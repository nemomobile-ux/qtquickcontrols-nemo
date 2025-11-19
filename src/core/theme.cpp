/*
 * Copyright (C) 2018-2025 Chupligin Sergey <neochapay@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#include "theme.h"
#include "logging.h"

#include <MDConfItem>
#include <QFile>
#include <QGuiApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QScreen>
#include <math.h>

static Theme* themeInstance = 0;

Theme::Theme(QObject* parent)
    : QObject(parent)
{
#ifndef UNIT_TEST
    // All sizes we get from LipstickSettings::exportScreenProperties()
    MDConfItem physicalDotsPerInchConf("/lipstick/screen/primary/physicalDotsPerInch");
    if (physicalDotsPerInchConf.value().isNull()) {
        QScreen* primaryScreen = QGuiApplication::primaryScreen();
        physicalDotsPerInchConf.set(primaryScreen->physicalDotsPerInch());
        physicalDotsPerInchConf.sync();
    }
#endif

#ifndef UNIT_TEST
    m_dpScaleFactorValue = std::make_shared<MDConfItem>(QStringLiteral("/nemo/apps/libglacier/dpScaleFactor"));
    m_dpScaleFactor = m_dpScaleFactorValue->value("1").toFloat();
#else
    m_dpScaleFactor = 1;
#endif

#ifndef UNIT_TEST
    MDConfItem dpi("/lipstick/screen/primary/physicalDotsPerInch");
    m_mmScaleFactor = dpi.value("1").toReal() / 2.45 / 10;
#else
    m_mmScaleFactor = 1;
#endif
    loadDefaultValue();

#ifndef UNIT_TEST
    m_themeValue = std::make_shared<MDConfItem>(QStringLiteral("/nemo/apps/libglacier/themePath"));
    m_theme = m_themeValue->value("/usr/share/themes/nemo.json").toString();

    connect(m_themeValue.get(), &MDConfItem::valueChanged, this, &Theme::themeValueChanged);
    connect(&dpi, &MDConfItem::valueChanged, this, &Theme::setThemeValues);
    connect(&physicalDotsPerInchConf, &MDConfItem::valueChanged, this, &Theme::setThemeValues);

    connect(m_dpScaleFactorValue.get(), &MDConfItem::valueChanged, [=]() {
        float newDpScaleFactor = m_dpScaleFactorValue->value("0").toFloat();
        if (newDpScaleFactor != m_dpScaleFactor) {
            m_dpScaleFactor = newDpScaleFactor;
            emit dpScaleFactorChanged();
            emit themeUpdated();
        }
    });
#endif
    if (!m_theme.isEmpty()) {
        loadTheme(m_theme);
    } else {
        loadDefaultValue();
    }
}

QObject* Theme::qmlInstance(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    if (!themeInstance) {
        themeInstance = new Theme();
    }
    return themeInstance;
}

bool Theme::loadTheme(QString fileName)
{
    QFile themeFile(fileName);
    if (fileName.isEmpty()) {
        qCWarning(lcNemoControlsCoreLog) << "Theme file is empty";
        return false;
    }

    if (!themeFile.exists()) {
        qCDebug(lcNemoControlsCoreLog) << "Theme file " << fileName << " not found";
        return false;
    }

    if (themeFile.size() == 0) {
        qCDebug(lcNemoControlsCoreLog) << "Theme file " << fileName << " is empty";
        return false;
    }
    if (fileName != m_theme) {
#ifndef UNIT_TEST
        m_themeValue->set(fileName);
#endif
        m_theme = fileName;
        setThemeValues();
    }
    return true;
}

float Theme::dp(float value)
{
    return value * m_dpScaleFactor;
}

float Theme::mm(float value)
{
    return value * m_mmScaleFactor;
}

void Theme::setThemeValues()
{
    QString themeJsonString;

    bool updated = false;

    QFile themeFile(m_theme);

    themeFile.open(QIODevice::ReadOnly | QIODevice::Text);
    themeJsonString = themeFile.readAll();
    themeFile.close();

    QJsonDocument t = QJsonDocument::fromJson(themeJsonString.toUtf8());
    QJsonObject theme = t.object();

    m_iconSizeLauncher = theme.value("iconSizeLauncher").toDouble();
    m_itemWidthExtraLarge = floor(theme.value("itemWidthExtraLarge").toDouble());
    m_itemWidthLarge = floor(theme.value("itemWidthLarge").toDouble());
    m_itemWidthMedium = floor(theme.value("itemWidthMedium").toDouble());
    m_itemWidthSmall = floor(theme.value("itemWidthSmall").toDouble());
    m_itemWidthExtraSmall = floor(theme.value("itemWidthExtraSmall").toDouble());
    m_itemHeightHuge = floor(theme.value("itemHeightHuge").toDouble());
    m_itemHeightExtraLarge = floor(theme.value("itemHeightExtraLarge").toDouble());
    m_itemHeightLarge = floor(theme.value("itemHeightLarge").toDouble());
    m_itemHeightMedium = floor(theme.value("itemHeightMedium").toDouble());
    m_itemHeightSmall = floor(theme.value("itemHeightSmall").toDouble());
    m_itemHeightExtraSmall = floor(theme.value("itemHeightExtraSmall").toDouble());
    m_itemSpacingHuge = floor(theme.value("itemSpacingHuge").toDouble());
    m_itemSpacingLarge = floor(theme.value("itemSpacingLarge").toDouble());
    m_itemSpacingMedium = floor(theme.value("itemSpacingMedium").toDouble());
    m_itemSpacingSmall = floor(theme.value("itemSpacingSmall").toDouble());
    m_itemSpacingExtraSmall = floor(theme.value("itemSpacingExtraSmall").toDouble());
    m_fontSizeExtraLarge = floor(theme.value("fontSizeExtraLarge").toInt());
    m_fontSizeLarge = floor(theme.value("fontSizeLarge").toInt());
    m_fontSizeMedium = floor(theme.value("fontSizeMedium").toInt());
    m_fontSizeSmall = floor(theme.value("fontSizeSmall").toInt());
    m_fontSizeTiny = floor(theme.value("fontSizeTiny").toInt());
    m_fontWeightLarge = theme.value("fontWeightLarge").toInt();
    m_fontWeightMedium = theme.value("fontWeightMedium").toInt();

    QFile fontFile;
    fontFile.setFileName(theme.value("fontPath").toString());
    if (!themeFile.exists()) {
        qCWarning(lcNemoControlsCoreLog) << "Font file " << fontFile.fileName() << " not found";
    } else {
        m_fontPath = theme.value("fontPath").toString();
        updated = true;
    }
    m_accentColor = theme.value("accentColor").toString();
    m_fillColor = theme.value("fillColor").toString();
    m_fillDarkColor = theme.value("fillDarkColor").toString();
    m_textColor = theme.value("textColor").toString();
    m_backgroundColor = theme.value("backgroundColor").toString();
    m_backgroundAccentColor = theme.value("backgroundAccentColor").toString();

    emit themeUpdated();
}

void Theme::themeValueChanged()
{
    QString themePath = m_themeValue->value().toString();
    if (!themePath.isEmpty() && QFile::exists(themePath)) {
        m_theme = themePath;
        setThemeValues();
    }
}

void Theme::loadDefaultValue()
{
    // Load defaults
    m_itemWidthExtraLarge = 450;
    m_itemWidthLarge = 320;
    m_itemWidthMedium = 240;
    m_itemWidthSmall = 120;
    m_itemWidthExtraSmall = 72;

    m_itemHeightHuge = 80;
    m_itemHeightExtraLarge = 75;
    m_itemHeightLarge = 63;
    m_itemHeightMedium = 50;
    m_itemHeightSmall = 40;
    m_itemHeightExtraSmall = 32;

    m_itemSpacingHuge = 48;
    m_itemSpacingLarge = 24;
    m_itemSpacingMedium = 18;
    m_itemSpacingSmall = 14;
    m_itemSpacingExtraSmall = 12;

    m_fontSizeExtraLarge = 44;
    m_fontSizeLarge = 24;
    m_fontSizeMedium = 20;
    m_fontSizeSmall = 18;
    m_fontSizeTiny = 14;
    m_fontWeightLarge = 63;
    m_fontWeightMedium = 25;
    m_fontPath = "/usr/share/fonts/google-opensans/OpenSans-Regular.ttf";

    m_accentColor = "#0091e5";
    m_fillColor = "#474747";
    m_fillDarkColor = "#313131";
    m_textColor = "#ffffff";
    m_backgroundColor = "#000000";
    m_backgroundAccentColor = "#ffffff";
}

float Theme::mmScaleFactor() const
{
    return m_mmScaleFactor;
}

float Theme::dpScaleFactor() const
{
    return m_dpScaleFactor;
}
