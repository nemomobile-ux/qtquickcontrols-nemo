/*
 * Copyright (C) 2013 Tomasz Olszak <olszak.tomasz@gmail.com>
 * Copyright (C) 2013 Andrea Bernabei <and.bernabei@gmail.com>
 * Copyright (C) 2017 Eetu Kahelin
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

#include "plugin.h"
#include "filteringmousearea.h"
#include "inversemousearea.h"
#include "nemofocussingleton.h"
#include "nemopage.h"
#include "nemowindow.h"
#include "ringindicator.h"
#include <QtQml>

QObject* getNemoFocus(QQmlEngine* engine, QJSEngine* scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    return NemoFocusSingleton::instance().get();
}

void QQuickNemoControlsExtensionPlugin::registerTypes(const char* uri)
{
    Q_ASSERT(uri == QLatin1String("Nemo.Controls"));
    qmlRegisterModule(uri, 2, 0);
    //@uri Nemo.Controls
    qmlRegisterSingletonType<QObject>(uri, 2, 0, "NemoFocus", getNemoFocus);
    qmlRegisterType<NemoWindow>(uri, 2, 0, "NemoWindow");
    qmlRegisterType<NemoPage>(uri, 2, 0, "NemoPage");
    qmlRegisterType<RingIndicator>(uri, 2, 0, "RingIndicator");
    qmlRegisterType<FilteringMouseArea>(uri, 2, 0, "FilteringMouseArea");
    qmlRegisterType<InverseMouseArea>(uri, 2, 0, "InverseMouseArea");
}
