/*
 * Copyright (C) 2013 Tomasz Olszak <olszak.tomasz@gmail.com>
 * Copyright (C) 2013 Andrea Bernabei <and.bernabei@gmail.com>
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

#include "qquicknemostyleextensionplugin.h"
#include <QtQml>
#include "nemotheme.h"

QQuickNemoStyleExtensionPlugin::QQuickNemoStyleExtensionPlugin(QObject *parent) :
    QQmlExtensionPlugin(parent)
{
}

static QObject * nemo_theme_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    return new NemoTheme();
}

void QQuickNemoStyleExtensionPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("QtQuick.Controls.Styles.Nemo"));
    QString reason = QString("Cannot be created");
    qmlRegisterUncreatableType<NemoTheme>(uri, 1, 0, "NemoTheme", reason);
    qmlRegisterUncreatableType<NemoThemeButton>(uri, 1, 0, "NemoThemeButton", reason);
    qmlRegisterUncreatableType<NemoThemeButtonPressedGradient>(uri, 1, 0, "NemoThemeButtonPressedGradient", reason);
    qmlRegisterUncreatableType<NemoThemeButtonText>(uri, 1, 0, "NemoThemeButtonText", reason);
    qmlRegisterUncreatableType<NemoThemeFont>(uri, 1, 0, "NemoThemeFont", reason);
    qmlRegisterUncreatableType<NemoThemeGroove>(uri, 1, 0, "NemoThemeGroove", reason);
    qmlRegisterUncreatableType<NemoThemeTextField>(uri, 1, 0, "NemoThemeTextField", reason);
    qmlRegisterSingletonType<QObject>(uri, 1, 0, "Theme", nemo_theme_provider);
}

void QQuickNemoStyleExtensionPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    QQmlExtensionPlugin::initializeEngine(engine,uri);
}
