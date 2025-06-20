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

#include <QtTest/QtTest>
#include "ut_imageprovider.h"
#include <nemoimageprovider.h>

void Ut_ImageProvider::init()
{
}

void Ut_ImageProvider::cleanup()
{
}

void Ut_ImageProvider::getImage()
{
    NemoImageProvider* imageProvider = new NemoImageProvider();
    QImage providerImage = imageProvider->requestImage(QString("file"), nullptr, QSize(100,100));

    QCOMPARE(providerImage.isNull(), false);
}

void Ut_ImageProvider::getWrongImage()
{
    NemoImageProvider* imageProvider = new NemoImageProvider();
    QImage providerImage = imageProvider->requestImage(QString("wrong"), nullptr, QSize(100,100));

    QCOMPARE(providerImage.isNull(), true);
}

void Ut_ImageProvider::getImageBySize()
{
    NemoImageProvider* imageProvider = new NemoImageProvider();
    QImage providerImage = imageProvider->requestImage(QString("file"), nullptr, QSize(100,150));

    QCOMPARE(providerImage.width(), 100);
    QCOMPARE(providerImage.height(), 150);
}

void Ut_ImageProvider::getPximap()
{
    NemoImageProvider* imageProvider = new NemoImageProvider();
    QPixmap providerPixmap = imageProvider->requestPixmap(QString("file"), nullptr, QSize(100,100));

    QCOMPARE(providerPixmap.isNull(), false);
}

void Ut_ImageProvider::getWrongPximap()
{
    NemoImageProvider* imageProvider = new NemoImageProvider();
    QPixmap providerPixmap = imageProvider->requestPixmap(QString("wrong"), nullptr, QSize(100,100));

    QCOMPARE(providerPixmap.isNull(), true);
}

void Ut_ImageProvider::getPximapBySize()
{
    NemoImageProvider* imageProvider = new NemoImageProvider();
    QPixmap providerPixmap = imageProvider->requestPixmap(QString("file"), nullptr, QSize(95,105));

    QCOMPARE(providerPixmap.width(), 95);
    QCOMPARE(providerPixmap.height(), 105);
}

QTEST_MAIN(Ut_ImageProvider)
