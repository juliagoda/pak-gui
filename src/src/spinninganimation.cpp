// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of CachyOS package manager based on "pak" application.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "spinninganimation.h"

#include "logger.h"


SpinningAnimation::SpinningAnimation() :
    animation(new QMovie(":/waiting.gif"), &QObject::deleteLater),
    animation2(new QMovie(":/waiting.gif"), &QObject::deleteLater),
    animation3(new QMovie(":/waiting.gif"), &QObject::deleteLater),
    small_animation(new QMovie(":/waiting-small.gif"), &QObject::deleteLater)
{
   // ...
}


void SpinningAnimation::startOnMainWidgets(const QPointer<QLabel>& first_label,
    const QPointer<QLabel>& second_label,
    const QPointer<QLabel>& third_label)
{
    if (!isValid(animation))
        return;

    if (!first_label->movie())
        first_label->setMovie(animation.get());
    first_label->show();
    if (!second_label->movie())
        second_label->setMovie(animation2.get());
    second_label->show();
    if (!third_label->movie())
        third_label->setMovie(animation3.get());
    third_label->show();
    animation->start();
    animation2->start();
    animation3->start();
    Logger::logger()->logDebug(QStringLiteral("Main animation started!"));
}


void SpinningAnimation::stopOnMainWidgets(const QPointer<QLabel>& first_label,
    const QPointer<QLabel>& second_label,
    const QPointer<QLabel>& third_label)
{
    if (!isValid(animation))
        return;

    first_label->hide();
    second_label->hide();
    third_label->hide();
    animation->stop();
    animation2->stop();
    animation3->stop();
    Logger::logger()->logDebug(QStringLiteral("Main animations stopped!"));
}


bool SpinningAnimation::isAnimationRunning() const
{
    return !animation.isNull() ? animation->state() == QMovie::Running : false;
}


bool SpinningAnimation::isSmallAnimationRunning() const
{
    return !small_animation.isNull() ? small_animation->state() == QMovie::Running : false;
}


template<> void SpinningAnimation::startOnWidget<1>(const QPointer<QLabel>& label)
{
    if (!isValid(animation))
        return;

    if (!label->movie())
        label->setMovie(animation.get());
    label->show();
    animation->start();
    Logger::logger()->logDebug(QStringLiteral("Animation started!"));
}


template<> void SpinningAnimation::startOnWidget<2>(const QPointer<QLabel>& label)
{
    if (!isValid(animation2))
        return;

    if (!label->movie())
        label->setMovie(animation2.get());
    label->show();
    animation2->start();
    Logger::logger()->logDebug(QStringLiteral("Animation started!"));
}


template<> void SpinningAnimation::startOnWidget<3>(const QPointer<QLabel>& label)
{
    if (!isValid(animation3))
        return;

    if (!label->movie())
        label->setMovie(animation3.get());
    label->show();
    animation3->start();
    Logger::logger()->logDebug(QStringLiteral("Animation started!"));
}


template<> void SpinningAnimation::stopOnWidget<1>(const QPointer<QLabel>& label)
{
    if (!isValid(animation))
        return;

    label->hide();
    animation->stop();
    Logger::logger()->logDebug(QStringLiteral("Animation stopped!"));
}


template<> void SpinningAnimation::stopOnWidget<2>(const QPointer<QLabel>& label)
{
    if (!isValid(animation2))
        return;

    label->hide();
    animation2->stop();
    Logger::logger()->logDebug(QStringLiteral("Animation stopped!"));
}


template<> void SpinningAnimation::stopOnWidget<3>(const QPointer<QLabel>& label)
{
    if (!isValid(animation3))
        return;

    label->hide();
    animation3->stop();
    Logger::logger()->logDebug(QStringLiteral("Animation stopped!"));
}


void SpinningAnimation::startSmallOnWidget(const QPointer<QLabel>& label)
{
    if (!isValid(small_animation))
        return;

    if (!label->movie())
        label->setMovie(small_animation.get());
    label->show();
    small_animation->start();
    Logger::logger()->logDebug(QStringLiteral("Small animation started!"));
}


void SpinningAnimation::stopSmallOnWidget(const QPointer<QLabel>& label)
{
    if (!isValid(small_animation))
        return;

    label->hide();
    small_animation->stop();
    Logger::logger()->logDebug(QStringLiteral("Small animation stopped!"));
}


bool SpinningAnimation::isValid(const QSharedPointer<QMovie>& animation)
{
    if (animation.isNull())
    {
        Logger::logger()->logDebug("Cannot toggle animation - animation instance doesn't exist");
        return false;
    }

    return true;
}
