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

#include "nemofocussingleton.h"

static std::shared_ptr<NemoFocusSingleton> _instance = nullptr;

NemoFocusSingleton::NemoFocusSingleton(QObject *parent)
    :m_edit(nullptr)
{
}

void NemoFocusSingleton::nemoregister(QObject* edit)
{
    if(edit != nullptr) {
        m_edit = std::make_shared<QObject>(edit);
    }
}

std::shared_ptr<NemoFocusSingleton> NemoFocusSingleton::instance()
{
    if (_instance == nullptr) {
        _instance = std::make_shared<NemoFocusSingleton>();
    }
    return _instance;
}

std::shared_ptr<QObject> NemoFocusSingleton::edit() const
{
    return m_edit;
}
