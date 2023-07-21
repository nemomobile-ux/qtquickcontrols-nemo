/*
 * Copyright (C) 2013 Andrea Bernabei <and.bernabei@gmail.com>
 * Copyright (C) 2021-2022 Chupligin Sergey <neochapay@gmail.com>
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

#ifndef NEMOWINDOW_H
#define NEMOWINDOW_H

#include "editfilter.h"
#include <QQuickWindow>

class NemoWindow : public QQuickWindow {
    Q_OBJECT
public:
    explicit NemoWindow(QWindow* parent = 0);
    Qt::ScreenOrientation primaryOrientation() const;

signals:
    void orientationChanged(Qt::ScreenOrientation orientation);

private:    
    EditFilter* m_filter;
    QScreen *m_screen;
};

#endif // NEMOWINDOW_H
