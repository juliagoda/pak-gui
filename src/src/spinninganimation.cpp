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
    small_animation(new QMovie(":/waiting-small.gif"), &QObject::deleteLater)
{
   // ...
}


void SpinningAnimation::startOnMainWidgets(QPointer<QLabel> first_label,
                                           QPointer<QLabel> second_label,
                                           QPointer<QLabel> third_label)
{
    if (!isValid(animation))
        return;

    first_label->setMovie(animation.get());
    first_label->show();
    second_label->setMovie(animation.get());
    second_label->show();
    third_label->setMovie(animation.get());
    third_label->show();
    animation->start();
    Logger::logger()->logDebug(QStringLiteral("Main animation started!"));
}


void SpinningAnimation::stopOnMainWidgets(QPointer<QLabel> first_label,
                                          QPointer<QLabel> second_label,
                                          QPointer<QLabel> third_label)
{
    if (!isValid(animation))
        return;

    first_label->hide();
    second_label->hide();
    third_label->hide();
    animation->stop();
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


void SpinningAnimation::startOnWidget(QPointer<QLabel> label)
{
    if (!isValid(animation))
        return;

    label->setMovie(animation.get());
    label->show();
    animation->start();
    Logger::logger()->logDebug(QStringLiteral("Animation started!"));
}


void SpinningAnimation::stopOnWidget(QPointer<QLabel> label)
{
    if (!isValid(animation))
        return;

    label->hide();
    animation->stop();
    Logger::logger()->logDebug(QStringLiteral("Animation stopped!"));
}


void SpinningAnimation::startSmallOnWidget(QPointer<QLabel> label)
{
    if (!isValid(small_animation))
        return;

    label->setMovie(small_animation.get());
    label->show();
    small_animation->start();
    Logger::logger()->logDebug(QStringLiteral("Small animation started!"));
}


void SpinningAnimation::stopSmallOnWidget(QPointer<QLabel> label)
{
    if (!isValid(small_animation))
        return;

    label->hide();
    small_animation->stop();
    Logger::logger()->logDebug(QStringLiteral("Small animation stopped!"));
}


bool SpinningAnimation::isValid(QSharedPointer<QMovie>& animation)
{
    if (animation.isNull())
    {
        Logger::logger()->logDebug("Cannot toggle animation - animation instance doesn't exist");
        return false;
    }

    return true;
}
