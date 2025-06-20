/*
 * Copyright (C) 2025 Chupligin Sergey <neochapay@gmail.com>
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

#include <QtTest/QtTest>
#include "ut_coretheme.h"
#include <theme.h>

void Ut_CoreTheme::init()
{
}

void Ut_CoreTheme::cleanup()
{
}

void Ut_CoreTheme::loadTheme()
{
    Theme* theme = new Theme();

    bool loadTheme = theme->loadTheme(QString(SOURCE_DIR) + "/tests/ut_coreTheme/testTheme.json");
    QCOMPARE(true, loadTheme);
    delete(theme);
}

void Ut_CoreTheme::loadThemeFail()
{
    Theme* theme = new Theme();

    bool loadTheme = theme->loadTheme(QString(SOURCE_DIR) + "/tests/ut_coreTheme/missingTheme.json");
    QCOMPARE(false, loadTheme);
    delete(theme);
}

void Ut_CoreTheme::checkThemeValues()
{
    Theme* theme = new Theme();

    theme->loadTheme(QString(SOURCE_DIR) + "/tests/ut_coreTheme/testTheme.json");
    QCOMPARE(1, theme->itemWidthExtraLarge());
    QCOMPARE(2, theme->itemWidthLarge());
    QCOMPARE(3, theme->itemWidthMedium());
    QCOMPARE(4, theme->itemWidthSmall());
    QCOMPARE(5, theme->itemWidthExtraSmall());
    QCOMPARE(6, theme->itemHeightHuge());
    QCOMPARE(7, theme->itemHeightExtraLarge());
    QCOMPARE(8, theme->itemHeightLarge());
    QCOMPARE(9, theme->itemHeightMedium());
    QCOMPARE(10, theme->itemHeightSmall());
    QCOMPARE(11, theme->itemHeightExtraSmall());
    QCOMPARE(12, theme->itemSpacingHuge());
    QCOMPARE(13, theme->itemSpacingLarge());
    QCOMPARE(14, theme->itemSpacingMedium());
    QCOMPARE(15, theme->itemSpacingSmall());
    QCOMPARE(16, theme->itemSpacingExtraSmall());
    QCOMPARE(17, theme->fontSizeExtraLarge());
    QCOMPARE(18, theme->fontSizeLarge());
    QCOMPARE(19, theme->fontSizeMedium());
    QCOMPARE(20, theme->fontSizeSmall());
    QCOMPARE(21, theme->fontSizeTiny());
    QCOMPARE(22, theme->fontWeightLarge());
    QCOMPARE(23, theme->fontWeightMedium());
    QCOMPARE("AwesomeFont", theme->fontPath());
    QCOMPARE("#000000", theme->accentColor());
    QCOMPARE("#111111", theme->fillColor());
    QCOMPARE("#222222", theme->fillDarkColor());
    QCOMPARE("#333333", theme->textColor());
    QCOMPARE("#444444", theme->backgroundColor());
    QCOMPARE("#555555", theme->backgroundAccentColor());
    QCOMPARE(1, theme->dpScaleFactor());
    QCOMPARE(1, theme->mmScaleFactor());
    delete(theme);
}

QTEST_MAIN(Ut_CoreTheme)
