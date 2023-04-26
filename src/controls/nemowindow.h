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
#include <QtCore/qnamespace.h>

class NemoWindow : public QQuickWindow {
    Q_OBJECT
    Q_PROPERTY(Qt::ScreenOrientations allowedOrientations READ allowedOrientations WRITE setAllowedOrientations NOTIFY allowedOrientationsChanged)
    Q_PROPERTY(Qt::ScreenOrientations defaultAllowedOrientations READ allowedOrientations)

    Q_PROPERTY(Qt::ScreenOrientation screenOrientation READ screenOrientation NOTIFY screenOrientationChanged)
    Q_PROPERTY(Qt::ScreenOrientation primaryOrientation READ primaryOrientation NOTIFY primaryOrientationChanged)
    Q_PROPERTY(bool isUiPortrait READ isUiPortrait NOTIFY isUiPortraitChanged)

public:
    explicit NemoWindow(QWindow* parent = 0);

    Qt::ScreenOrientations allowedOrientations() const;
    const Qt::ScreenOrientations defaultAllowedOrientations() const;

    void setAllowedOrientations(Qt::ScreenOrientations allowed);

    Qt::ScreenOrientation screenOrientation() const;
    Qt::ScreenOrientation primaryOrientation() const;
    bool isUiPortrait();

signals:
    void allowedOrientationsChanged();
    void desktopModeChanged();
    void screenOrientationChanged();
    void primaryOrientationChanged();
    void isUiPortraitChanged();

private slots:
    void orientationChanged(Qt::ScreenOrientation orientation);
    void m_primaryOrientationChanged(Qt::ScreenOrientation orientation);

    void onSizeChanged(int arg);

private:
    // This is the global allowed orientations settings:
    // it's the settings used when the current Page doesn't specify any allowedOrientations, otherwise
    // allowedOrientations of that Page is used
    Qt::ScreenOrientations m_allowedOrientations;
    Qt::ScreenOrientations m_defaultAllowedOrientations;

    Qt::ScreenOrientation m_screenOrientation;
    Qt::ScreenOrientation m_primaryOrientation;
    QScreen* m_primaryScreen;
    bool m_isUiPortrait;
    bool m_currentDesktopMode;

    EditFilter* m_filter;
};

#endif // NEMOWINDOW_H
