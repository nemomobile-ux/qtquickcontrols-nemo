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

#include "ut_nemopage.h"
#include "qtestcase.h"
#include <QtTest/QtTest>
#include <nemopage.h>

void Ut_NemoPage::init()
{
}

void Ut_NemoPage::cleanup()
{
}

void Ut_NemoPage::getDefaultAllowedOrientation()
{
    NemoPage *page = new NemoPage();
    QCOMPARE(page->allowedOrientations(), Qt::PrimaryOrientation);
}

void Ut_NemoPage::setAllowedOrientation()
{
    NemoPage *page = new NemoPage();
    page->setAllowedOrientations(Qt::PortraitOrientation);
    QCOMPARE(page->allowedOrientations(), Qt::PortraitOrientation);
}

QTEST_MAIN(Ut_NemoPage)
