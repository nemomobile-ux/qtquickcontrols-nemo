/*
 * Copyright (C) 2013 Andrea Bernabei <and.bernabei@gmail.com>
 * Copyright (C) 2021-2023 Chupligin Sergey <neochapay@gmail.com>
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

#include "nemowindow.h"
#include <QScreen>

NemoWindow::NemoWindow(QWindow* parent)
    : QQuickWindow(parent)
{
    m_filter = new EditFilter();
    this->installEventFilter(m_filter);

    m_screen = this->screen();
    connect(m_screen, &QScreen::orientationChanged, this, &NemoWindow::orientationChanged);
}

Qt::ScreenOrientation NemoWindow::primaryOrientation() const
{

    return m_screen->primaryOrientation();
}

void NemoWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Escape:
    case Qt::Key_Return:
    case Qt::Key_Backspace:
    case Qt::Key_Left:
        emit goBack();
        break;
    }
}
