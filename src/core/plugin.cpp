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

#include "plugin.h"
#include "nemoimageprovider.h"
#include "theme.h"
#include <QtQml>

void QQuickNemoControlsExtensionPlugin::registerTypes(const char* uri)
{
    Q_ASSERT(uri == QLatin1String("Nemo"));
    qmlRegisterModule(uri, 2, 0);
    qmlRegisterSingletonType<Theme>(uri, 1, 0, "Theme", &Theme::qmlInstance);
}

void QQuickNemoControlsExtensionPlugin::initializeEngine(QQmlEngine* engine, const char* uri)
{
    engine->addImageProvider(QLatin1String("theme"), new NemoImageProvider);
}
