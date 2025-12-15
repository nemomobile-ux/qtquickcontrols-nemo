/*
 * Copyright (C) 2017 Eetu Kahelin
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

#ifndef NEMOFOCUSSINGLETON_H
#define NEMOFOCUSSINGLETON_H

#include <QObject>

class NemoFocusSingleton : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(NemoFocusSingleton)

public:
    NemoFocusSingleton(QObject* parent = nullptr);
    Q_INVOKABLE void nemoregister(QObject* edit);
    std::shared_ptr<QObject> edit() const;

    static std::shared_ptr<NemoFocusSingleton> instance();

private:
    std::shared_ptr<QObject> m_edit;
};

#endif // NEMOFOCUSSINGLETON_H
