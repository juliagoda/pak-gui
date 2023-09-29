// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of  package manager based on "pak" application.
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
    animation{new QMovie(":/waiting.gif")},
    animation2{new QMovie(":/waiting.gif")},
    animation3{new QMovie(":/waiting.gif")},
    small_animation{new QMovie(":/waiting-small.gif")}
{
   // ...
}


void SpinningAnimation::startOnMainWidgets(const QPointer<QLabel>& first_label,
                                           const QPointer<QLabel>& second_label,
                                           const QPointer<QLabel>& third_label)
{
    if (!isValid(animation))
        return;

    restartMovie(first_label, animation);
    first_label->show();
    restartMovie(second_label, animation2);
    second_label->show();
    restartMovie(third_label, animation3);
    third_label->show();

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

    restartMovie(label, animation);
    label->show();
    Logger::logger()->logDebug(QStringLiteral("Animation started!"));
}


template<> void SpinningAnimation::startOnWidget<2>(const QPointer<QLabel>& label)
{
    if (!isValid(animation2))
        return;

    restartMovie(label, animation2);
    label->show();
    Logger::logger()->logDebug(QStringLiteral("Animation started!"));
}


template<> void SpinningAnimation::startOnWidget<3>(const QPointer<QLabel>& label)
{
    if (!isValid(animation3))
        return;

    restartMovie(label, animation3);
    label->show();
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

    restartMovie(label, small_animation);
    label->show();
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


bool SpinningAnimation::isValid(const QScopedPointer<QMovie>& animation)
{
    if (animation.isNull())
    {
        Logger::logger()->logDebug("Cannot toggle animation - animation instance doesn't exist");
        return false;
    }

    return true;
}


void SpinningAnimation::restartMovie(const QPointer<QLabel>& label,
                                     const QScopedPointer<QMovie>& animation)
{
    if (!label->movie())
    {
        label->setMovie(animation.get());
        label->movie()->start();
        return;
    }

    label->movie()->jumpToFrame(1);
    label->movie()->start();
}
