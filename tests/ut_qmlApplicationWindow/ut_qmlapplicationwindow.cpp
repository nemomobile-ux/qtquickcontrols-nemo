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

#include "ut_qmlapplicationwindow.h"
#include <QtTest/QtTest>
#include <qmltest.h>

void Ut_QmlApplicationWindow::init()
{
}

void Ut_QmlApplicationWindow::cleanup()
{
}

void Ut_QmlApplicationWindow::checkWarning()
{
    QmlTest* test = new QmlTest(QString(SOURCE_DIR) + "/tests/ut_qmlApplicationWindow/test.qml");
    QCOMPARE(test->warnings(), 0);
}

QTEST_MAIN(Ut_QmlApplicationWindow)
