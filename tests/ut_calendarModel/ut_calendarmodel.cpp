/*
 * Copyright (C) 2026 Chupligin Sergey <neochapay@gmail.com>
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

#include "ut_calendarmodel.h"
#include "calendarmodel.h"

#include <QtTest/QtTest>

void Ut_CalendarModel::initialState()
{
    CalendarModel model;
    QCOMPARE(model.selectedDate(), model.currentDate());
    QVERIFY(model.rowCount() > 0);
    QVERIFY(model.rowCount() % 7 == 0);
}

void Ut_CalendarModel::selectDateEmitsReset()
{
    CalendarModel model;
    QSignalSpy aboutToResetSpy(&model, &QAbstractItemModel::modelAboutToBeReset);
    QSignalSpy resetSpy(&model, &QAbstractItemModel::modelReset);
    QSignalSpy selectedSpy(&model, &CalendarModel::selectedDateChanged);

    const QDate newDate = model.selectedDate().addMonths(1);
    model.setSelectedDate(newDate);

    QCOMPARE(model.selectedDate(), newDate);
    QCOMPARE(selectedSpy.count(), 1);
    QCOMPARE(aboutToResetSpy.count(), 1);
    QCOMPARE(resetSpy.count(), 1);
    QVERIFY(model.rowCount() > 0);
}

void Ut_CalendarModel::marksSelectedDay()
{
    CalendarModel model;
    const QDate selected = QDate::currentDate().addDays(1);
    model.setSelectedDate(selected);

    bool found = false;
    for (int row = 0; row < model.rowCount(); ++row) {
        const QModelIndex idx = model.index(row, 0);
        const QDate date = model.data(idx, Qt::UserRole + 4).toDate();
        const bool isSelected = model.data(idx, Qt::UserRole + 2).toBool();
        if (date == selected) {
            QVERIFY(isSelected);
            found = true;
        } else if (isSelected) {
            QFAIL("Unexpected day marked as selected");
        }
    }
    QVERIFY(found);
}

QTEST_MAIN(Ut_CalendarModel)
