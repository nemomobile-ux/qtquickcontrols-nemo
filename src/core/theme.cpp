/*
 * Copyright (C) 2018-2021 Chupligin Sergey <neochapay@gmail.com>
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
#include "sizing.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <math.h>

Theme::Theme(QObject* parent)
    : QObject(parent)
{
    size = new Sizing;

    loadDefaultValue();

    m_themeValue = new MDConfItem(QStringLiteral("/nemo/apps/libglacier/themePath"));
    m_theme = m_themeValue->value().toString();

    connect(m_themeValue, &MDConfItem::valueChanged, this, &Theme::themeValueChanged);
    connect(size, &Sizing::dpScaleFactorChanged, this, &Theme::setThemeValues);

    if (!m_theme.isEmpty()) {
        loadTheme(m_theme);
    }
}

bool Theme::loadTheme(QString fileName)
{
    QFile themeFile(fileName);

    if (!themeFile.exists()) {
        qCDebug(lcNemoControlsCoreLog) << "Theme file " << fileName << " not found";
        return false;
    }

    if (themeFile.size() == 0) {
        qCDebug(lcNemoControlsCoreLog) << "Theme file " << fileName << " is empty";
        return false;
    }

    if (fileName != m_theme) {
        m_themeValue->set(fileName);
    } else {
        setThemeValues();
    }
    return true;
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

    if (theme.value("iconSizeLauncher").toString().toFloat() != 0 && theme.value("iconSizeLauncher").toString().toFloat() != m_iconSizeLauncher) {
        m_iconSizeLauncher = theme.value("iconSizeLauncher").toString().toFloat();
        emit iconSizeLauncherChanged();
        updated = true;
    }

    if (theme.value("itemWidthExtraLarge").toString().toFloat() != 0 && floor(theme.value("itemWidthExtraLarge").toString().toFloat()) != m_itemWidthExtraLarge) {
        m_itemWidthExtraLarge = floor(theme.value("itemWidthExtraLarge").toString().toFloat() * size->dpScaleFactor());
        emit itemWidthExtraLargeChanged();
        updated = true;
    }
    if (theme.value("itemWidthLarge").toString().toFloat() != 0 && floor(theme.value("itemWidthLarge").toString().toFloat()) != m_itemWidthLarge) {
        m_itemWidthLarge = floor(theme.value("itemWidthLarge").toString().toFloat() * size->dpScaleFactor());
        emit itemWidthLargeChanged();
        updated = true;
    }
    if (theme.value("itemWidthMedium").toString().toFloat() != 0 && floor(theme.value("itemWidthMedium").toString().toFloat()) != m_itemWidthMedium) {
        m_itemWidthMedium = floor(theme.value("itemWidthMedium").toString().toFloat() * size->dpScaleFactor());
        emit itemWidthMediumChanged();
        updated = true;
    }
    if (theme.value("itemWidthSmall").toString().toFloat() != 0 && floor(theme.value("itemWidthSmall").toString().toFloat()) != m_itemWidthSmall) {
        m_itemWidthSmall = floor(theme.value("itemWidthSmall").toString().toFloat() * size->dpScaleFactor());
        emit itemWidthSmallChanged();
        updated = true;
    }
    if (theme.value("itemWidthExtraSmall").toString().toFloat() != 0 && floor(theme.value("itemWidthExtraSmall").toString().toFloat()) != m_itemWidthExtraSmall) {
        m_itemWidthExtraSmall = floor(theme.value("itemWidthExtraSmall").toString().toFloat() * size->dpScaleFactor());
        emit itemWidthExtraSmallChanged();
        updated = true;
    }

    if (theme.value("itemHeightHuge").toString().toFloat() != 0 && floor(theme.value("itemHeightHuge").toString().toFloat()) != m_itemHeightHuge) {
        m_itemHeightHuge = floor(theme.value("itemHeightHuge").toString().toFloat() * size->dpScaleFactor());
        emit itemHeightHugeChanged();
        updated = true;
    }
    if (theme.value("itemHeightExtraLarge").toString().toFloat() != 0 && floor(theme.value("itemHeightExtraLarge").toString().toFloat()) != m_itemHeightExtraLarge) {
        m_itemHeightExtraLarge = floor(theme.value("itemHeightExtraLarge").toString().toFloat() * size->dpScaleFactor());
        emit itemHeightExtraLargeChanged();
        updated = true;
    }
    if (theme.value("itemHeightLarge").toString().toFloat() != 0 && floor(theme.value("itemHeightLarge").toString().toFloat()) != m_itemHeightLarge) {
        m_itemHeightLarge = floor(theme.value("itemHeightLarge").toString().toFloat() * size->dpScaleFactor());
        emit itemHeightLargeChanged();
        updated = true;
    }
    if (theme.value("itemHeightMedium").toString().toFloat() != 0 && floor(theme.value("itemHeightMedium").toString().toFloat()) != m_itemHeightMedium) {
        m_itemHeightMedium = floor(theme.value("itemHeightMedium").toString().toFloat() * size->dpScaleFactor());
        emit itemHeightMediumChanged();
        updated = true;
    }
    if (theme.value("itemHeightSmall").toString().toFloat() != 0 && floor(theme.value("itemHeightSmall").toString().toFloat()) != m_itemHeightSmall) {
        m_itemHeightSmall = floor(theme.value("itemHeightSmall").toString().toFloat() * size->dpScaleFactor());
        emit itemHeightSmallChanged();
        updated = true;
    }
    if (theme.value("itemHeightExtraSmall").toString().toFloat() != 0 && floor(theme.value("itemHeightExtraSmall").toString().toFloat()) != m_itemHeightExtraSmall) {
        m_itemHeightExtraSmall = floor(theme.value("itemHeightExtraSmall").toString().toFloat() * size->dpScaleFactor());
        emit itemHeightExtraSmallChanged();
        updated = true;
    }

    if (theme.value("itemSpacingHuge").toString().toFloat() != 0 && floor(theme.value("itemSpacingHuge").toString().toFloat()) != m_itemSpacingHuge) {
        m_itemSpacingHuge = floor(theme.value("itemSpacingHuge").toString().toFloat() * size->dpScaleFactor());
        emit itemSpacingHugeChanged();
        updated = true;
    }
    if (theme.value("itemSpacingLarge").toString().toFloat() != 0 && floor(theme.value("itemSpacingLarge").toString().toFloat()) != m_itemSpacingLarge) {
        m_itemSpacingLarge = floor(theme.value("itemSpacingLarge").toString().toFloat() * size->dpScaleFactor());
        emit itemSpacingLargeChanged();
        updated = true;
    }
    if (theme.value("itemSpacingMedium").toString().toFloat() != 0 && floor(theme.value("itemSpacingMedium").toString().toFloat()) != m_itemSpacingMedium) {
        m_itemSpacingMedium = floor(theme.value("itemSpacingMedium").toString().toFloat() * size->dpScaleFactor());
        emit itemSpacingMediumChanged();
        updated = true;
    }
    if (theme.value("itemSpacingSmall").toString().toFloat() != 0 && floor(theme.value("itemSpacingSmall").toString().toFloat()) != m_itemSpacingSmall) {
        m_itemSpacingSmall = floor(theme.value("itemSpacingSmall").toString().toFloat() * size->dpScaleFactor());
        emit itemSpacingSmallChanged();
        updated = true;
    }
    if (theme.value("itemSpacingExtraSmall").toString().toFloat() != 0 && floor(theme.value("itemSpacingExtraSmall").toString().toFloat()) != m_itemSpacingExtraSmall) {
        m_itemSpacingExtraSmall = floor(theme.value("itemSpacingExtraSmall").toString().toFloat() * size->dpScaleFactor());
        emit itemSpacingExtraSmallChanged();
        updated = true;
    }

    if (theme.value("fontSizeExtraLarge").toInt() != 0 && floor(theme.value("fontSizeExtraLarge").toInt()) != m_fontSizeExtraLarge) {
        m_fontSizeExtraLarge = floor(theme.value("fontSizeExtraLarge").toInt() * size->dpScaleFactor());
        emit fontSizeExtraLargeChanged();
        updated = true;
    }
    if (theme.value("fontSizeLarge").toInt() != 0 && floor(theme.value("fontSizeLarge").toInt()) != m_fontSizeLarge) {
        m_fontSizeLarge = floor(theme.value("fontSizeLarge").toInt() * size->dpScaleFactor());
        emit fontSizeLargeChanged();
        updated = true;
    }
    if (theme.value("fontSizeMedium").toInt() != 0 && floor(theme.value("fontSizeMedium").toInt()) != m_fontSizeMedium) {
        m_fontSizeMedium = floor(theme.value("fontSizeMedium").toInt() * size->dpScaleFactor());
        emit fontSizeMediumChanged();
        updated = true;
    }
    if (theme.value("fontSizeSmall").toInt() != 0 && floor(theme.value("fontSizeSmall").toInt()) != m_fontSizeSmall) {
        m_fontSizeSmall = floor(theme.value("fontSizeSmall").toInt() * size->dpScaleFactor());
        emit fontSizeSmallChanged();
        updated = true;
    }
    if (theme.value("fontSizeTiny").toInt() != 0 && floor(theme.value("fontSizeTiny").toInt()) != m_fontSizeTiny) {
        m_fontSizeTiny = floor(theme.value("fontSizeTiny").toInt() * size->dpScaleFactor());
        emit fontSizeTinyChanged();
        updated = true;
    }
    if (theme.value("fontWeightLarge").toInt() != 0 && theme.value("fontWeightLarge").toInt() != m_fontWeightLarge) {
        m_fontWeightLarge = theme.value("fontWeightLarge").toInt() * size->dpScaleFactor();
        emit fontWeightLargeChanged();
        updated = true;
    }
    if (theme.value("fontWeightMedium").toInt() != 0 && theme.value("fontWeightMedium").toInt() != m_fontWeightMedium) {
        m_fontWeightMedium = theme.value("fontWeightMedium").toInt() * size->dpScaleFactor();
        emit fontWeightMediumChanged();
        updated = true;
    }

    if (theme.value("fontPath").toString() != "" && theme.value("fontPath").toString() != m_fontPath) {
        QFile fontFile;
        fontFile.setFileName(theme.value("fontPath").toString());
        if (!themeFile.exists()) {
            qCDebug(lcNemoControlsCoreLog) << "Font file " << fontFile.fileName() << " not found";
        } else {
            m_fontPath = theme.value("fontPath").toString();
            emit fontPathChanged();
            updated = true;
        }
    }

    if (theme.value("accentColor").toString() != "" && theme.value("accentColor").toString() != m_accentColor) {
        m_accentColor = theme.value("accentColor").toString();
        emit accentColorChanged();
        updated = true;
    }
    if (theme.value("fillColor").toString() != "" && theme.value("fillColor").toString() != m_fillColor) {
        m_fillColor = theme.value("fillColor").toString();
        emit fillColorChanged();
        updated = true;
    }
    if (theme.value("fillDarkColor").toString() != "" && theme.value("fillDarkColor").toString() != m_fillDarkColor) {
        m_fillDarkColor = theme.value("fillDarkColor").toString();
        emit fillDarkColorChanged();
        updated = true;
    }
    if (theme.value("textColor").toString() != "" && theme.value("textColor").toString() != m_textColor) {
        m_textColor = theme.value("textColor").toString();
        emit textColorChanged();
        updated = true;
    }
    if (theme.value("backgroundColor").toString() != "" && theme.value("backgroundColor").toString() != m_backgroundColor) {
        m_backgroundColor = theme.value("backgroundColor").toString();
        emit backgroundColorChanged();
        updated = true;
    }
    if (theme.value("backgroundAccentColor").toString() != "" && theme.value("backgroundAccentColor").toString() != m_backgroundAccentColor) {
        m_backgroundAccentColor = theme.value("backgroundAccentColor").toString();
        emit backgroundAccentColorChanged();
        updated = true;
    }

    if (updated) {
        emit themeUpdate();
    }
}

void Theme::themeValueChanged()
{
    m_theme = m_themeValue->value().toString();
    setThemeValues();
}

void Theme::loadDefaultValue()
{
    // Load defaults
    m_itemWidthExtraLarge = floor(450 * size->dpScaleFactor());
    m_itemWidthLarge = floor(320 * size->dpScaleFactor());
    m_itemWidthMedium = floor(240 * size->dpScaleFactor());
    m_itemWidthSmall = floor(120 * size->dpScaleFactor());
    m_itemWidthExtraSmall = floor(72 * size->dpScaleFactor());

    m_itemHeightHuge = floor(80 * size->dpScaleFactor());
    m_itemHeightExtraLarge = floor(75 * size->dpScaleFactor());
    m_itemHeightLarge = floor(63 * size->dpScaleFactor());
    m_itemHeightMedium = floor(50 * size->dpScaleFactor());
    m_itemHeightSmall = floor(40 * size->dpScaleFactor());
    m_itemHeightExtraSmall = floor(32 * size->dpScaleFactor());

    m_itemSpacingHuge = floor(48 * size->dpScaleFactor());
    m_itemSpacingLarge = floor(24 * size->dpScaleFactor());
    m_itemSpacingMedium = floor(18 * size->dpScaleFactor());
    m_itemSpacingSmall = floor(14 * size->dpScaleFactor());
    m_itemSpacingExtraSmall = floor(12 * size->dpScaleFactor());

    m_fontSizeExtraLarge = floor(44 * size->dpScaleFactor());
    m_fontSizeLarge = floor(24 * size->dpScaleFactor());
    m_fontSizeMedium = floor(20 * size->dpScaleFactor());
    m_fontSizeSmall = floor(18 * size->dpScaleFactor());
    m_fontSizeTiny = floor(14 * size->dpScaleFactor());
    m_fontWeightLarge = 63 * size->dpScaleFactor();
    m_fontWeightMedium = 25 * size->dpScaleFactor();
    m_fontPath = "/usr/share/fonts/google-opensans/OpenSans-Regular.ttf";

    m_accentColor = "#0091e5";
    m_fillColor = "#474747";
    m_fillDarkColor = "#313131";
    m_textColor = "#ffffff";
    m_backgroundColor = "#000000";
    m_backgroundAccentColor = "#ffffff";
}

qreal Theme::itemWidthExtraLarge() const
{
    return m_itemWidthExtraLarge;
}

void Theme::setItemWidthExtraLarge(qreal newItemWidthExtraLarge)
{
    if (qFuzzyCompare(m_itemWidthExtraLarge, newItemWidthExtraLarge))
        return;
    m_itemWidthExtraLarge = newItemWidthExtraLarge;
    emit itemWidthExtraLargeChanged();
}
