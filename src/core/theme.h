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

#ifndef THEME_H
#define THEME_H

#include <MDConfItem>
#include <QObject>
#include <QQmlEngine>

class Theme : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(Theme)

    Q_PROPERTY(float mmScaleFactor READ mmScaleFactor NOTIFY mmScaleFactorChanged)
    Q_PROPERTY(float dpScaleFactor READ dpScaleFactor NOTIFY dpScaleFactorChanged)

    Q_PROPERTY(qreal iconSizeLauncher READ iconSizeLauncher NOTIFY themeUpdated)

    Q_PROPERTY(qreal itemWidthExtraLarge READ itemWidthExtraLarge NOTIFY themeUpdated)
    Q_PROPERTY(qreal itemWidthLarge READ itemWidthLarge NOTIFY themeUpdated)
    Q_PROPERTY(qreal itemWidthMedium READ itemWidthMedium NOTIFY themeUpdated)
    Q_PROPERTY(qreal itemWidthSmall READ itemWidthSmall NOTIFY themeUpdated)
    Q_PROPERTY(qreal itemWidthExtraSmall READ itemWidthExtraSmall NOTIFY themeUpdated)

    Q_PROPERTY(qreal itemHeightHuge READ itemHeightHuge NOTIFY themeUpdated)
    Q_PROPERTY(qreal itemHeightExtraLarge READ itemHeightExtraLarge NOTIFY themeUpdated)
    Q_PROPERTY(qreal itemHeightLarge READ itemHeightLarge NOTIFY themeUpdated)
    Q_PROPERTY(qreal itemHeightMedium READ itemHeightMedium NOTIFY themeUpdated)
    Q_PROPERTY(qreal itemHeightSmall READ itemHeightSmall NOTIFY themeUpdated)
    Q_PROPERTY(qreal itemHeightExtraSmall READ itemHeightExtraSmall NOTIFY themeUpdated)

    Q_PROPERTY(qreal itemSpacingHuge READ itemSpacingHuge NOTIFY themeUpdated)
    Q_PROPERTY(qreal itemSpacingLarge READ itemSpacingLarge NOTIFY themeUpdated)
    Q_PROPERTY(qreal itemSpacingMedium READ itemSpacingMedium NOTIFY themeUpdated)
    Q_PROPERTY(qreal itemSpacingSmall READ itemSpacingSmall NOTIFY themeUpdated)
    Q_PROPERTY(qreal itemSpacingExtraSmall READ itemSpacingExtraSmall NOTIFY themeUpdated)

    Q_PROPERTY(int fontSizeExtraLarge READ fontSizeExtraLarge NOTIFY themeUpdated)
    Q_PROPERTY(int fontSizeLarge READ fontSizeLarge NOTIFY themeUpdated)
    Q_PROPERTY(int fontSizeMedium READ fontSizeMedium NOTIFY themeUpdated)
    Q_PROPERTY(int fontSizeSmall READ fontSizeSmall NOTIFY themeUpdated)
    Q_PROPERTY(int fontSizeTiny READ fontSizeTiny NOTIFY themeUpdated)
    Q_PROPERTY(int fontWeightLarge READ fontWeightLarge NOTIFY themeUpdated)
    Q_PROPERTY(int fontWeightMedium READ fontWeightMedium NOTIFY themeUpdated)

    Q_PROPERTY(QString fontPath READ fontPath NOTIFY themeUpdated)

    Q_PROPERTY(QString accentColor READ accentColor NOTIFY themeUpdated)
    Q_PROPERTY(QString fillColor READ fillColor NOTIFY themeUpdated)
    Q_PROPERTY(QString fillDarkColor READ fillDarkColor NOTIFY themeUpdated)
    Q_PROPERTY(QString textColor READ textColor NOTIFY themeUpdated)
    Q_PROPERTY(QString backgroundColor READ backgroundColor NOTIFY themeUpdated)
    Q_PROPERTY(QString backgroundAccentColor READ backgroundAccentColor NOTIFY themeUpdated)
    Q_PROPERTY(QString themePath READ themePath NOTIFY themeUpdated)

public:
    explicit Theme(QObject* parent = nullptr);
    static QObject* qmlInstance(QQmlEngine* engine, QJSEngine* scriptEngine);

    Q_INVOKABLE bool loadTheme(const QString fileName);
    Q_INVOKABLE float dp(float value);
    Q_INVOKABLE float mm(float value);

    qreal itemWidthExtraLarge() const { return m_itemWidthExtraLarge * m_dpScaleFactor; }
    qreal itemWidthLarge() const { return m_itemWidthLarge * m_dpScaleFactor; }
    qreal itemWidthMedium() const { return m_itemWidthMedium * m_dpScaleFactor; }
    qreal itemWidthSmall() const { return m_itemWidthSmall * m_dpScaleFactor; }
    qreal itemWidthExtraSmall() const { return m_itemWidthExtraSmall * m_dpScaleFactor; }

    qreal itemHeightHuge() const { return m_itemHeightHuge * m_dpScaleFactor; }
    qreal itemHeightExtraLarge() const { return m_itemHeightExtraLarge * m_dpScaleFactor; }
    qreal itemHeightLarge() const { return m_itemHeightLarge * m_dpScaleFactor; }
    qreal itemHeightMedium() const { return m_itemHeightMedium * m_dpScaleFactor; }
    qreal itemHeightSmall() const { return m_itemHeightSmall * m_dpScaleFactor; }
    qreal itemHeightExtraSmall() const { return m_itemHeightExtraSmall * m_dpScaleFactor; }

    qreal itemSpacingHuge() const { return m_itemSpacingHuge * m_dpScaleFactor; }
    qreal itemSpacingLarge() const { return m_itemSpacingLarge * m_dpScaleFactor; }
    qreal itemSpacingMedium() const { return m_itemSpacingMedium * m_dpScaleFactor; }
    qreal itemSpacingSmall() const { return m_itemSpacingSmall * m_dpScaleFactor; }
    qreal itemSpacingExtraSmall() const { return m_itemSpacingExtraSmall * m_dpScaleFactor; }

    int fontSizeExtraLarge() const { return m_fontSizeExtraLarge * m_dpScaleFactor; }
    int fontSizeLarge() const { return m_fontSizeLarge * m_dpScaleFactor; }
    int fontSizeMedium() const { return m_fontSizeMedium * m_dpScaleFactor; }
    int fontSizeSmall() const { return m_fontSizeSmall * m_dpScaleFactor; }
    int fontSizeTiny() const { return m_fontSizeTiny * m_dpScaleFactor; }
    int fontWeightLarge() const { return m_fontWeightLarge * m_dpScaleFactor; }
    int fontWeightMedium() const { return m_fontWeightMedium * m_dpScaleFactor; }

    QString fontPath() const { return m_fontPath; }

    QString accentColor() const { return m_accentColor; }
    QString fillColor() const { return m_fillColor; }
    QString fillDarkColor() const { return m_fillDarkColor; }
    QString textColor() const { return m_textColor; }
    QString backgroundColor() const { return m_backgroundColor; }
    QString backgroundAccentColor() const { return m_backgroundAccentColor; }
    qreal iconSizeLauncher() const { return m_iconSizeLauncher; }
    QString themePath() const { return m_theme; }

    float mmScaleFactor() const;
    float dpScaleFactor() const;

signals:
    void themeUpdated();
    void desktopModeChanged();
    void mmScaleFactorChanged();
    void dpScaleFactorChanged();

private slots:
    void themeValueChanged();

private:
    qreal m_iconSizeLauncher; // 86 or 108 or 128 or 256

    qreal m_itemWidthExtraLarge; // 450
    qreal m_itemWidthLarge; // 320
    qreal m_itemWidthMedium; // 240
    qreal m_itemWidthSmall; // 120
    qreal m_itemWidthExtraSmall; // 72

    qreal m_itemHeightHuge; // 80
    qreal m_itemHeightExtraLarge; // 75
    qreal m_itemHeightLarge; // 63
    qreal m_itemHeightMedium; // 50
    qreal m_itemHeightSmall; // 40
    qreal m_itemHeightExtraSmall; // 32

    qreal m_itemSpacingHuge; // 40
    qreal m_itemSpacingLarge; // 20
    qreal m_itemSpacingMedium; // 15
    qreal m_itemSpacingSmall; // 10
    qreal m_itemSpacingExtraSmall; // 8

    int m_fontSizeExtraLarge; // 44
    int m_fontSizeLarge; // 35
    int m_fontSizeMedium; // 28
    int m_fontSizeSmall; // 24
    int m_fontSizeTiny; // 16
    int m_fontWeightLarge; // 63
    int m_fontWeightMedium; // 25
    QString m_fontPath; //???

    QString m_accentColor; // #0091e5
    QString m_fillColor; // #474747
    QString m_fillDarkColor; // #313131
    QString m_textColor; // #ffffff
    QString m_backgroundColor; // #000000
    QString m_backgroundAccentColor; // #ffffff

    QString m_theme;

    void loadDefaultValue();
    void setThemeValues();

    MDConfItem* m_dpScaleFactorValue;
    MDConfItem* m_themeValue;
    float m_mmScaleFactor;
    float m_dpScaleFactor;
};

#endif // THEME_H
