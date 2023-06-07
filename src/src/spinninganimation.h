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

#pragma once

#include <QMovie>
#include <QSharedPointer>
#include <QLabel>


class SpinningAnimation
{
public:
    explicit SpinningAnimation();
    virtual ~SpinningAnimation() = default;

    void startOnWidget(QPointer<QLabel> label);
    void stopOnWidget(QPointer<QLabel> label);
    void startOnMainWidgets(QPointer<QLabel> first_label,
                            QPointer<QLabel> second_label,
                            QPointer<QLabel> third_label);
    void stopOnMainWidgets(QPointer<QLabel> first_label,
                           QPointer<QLabel> second_label,
                           QPointer<QLabel> third_label);
    bool isAnimationRunning() const;
    bool isSmallAnimationRunning() const;

public Q_SLOTS:
    void startSmallOnWidget(QPointer<QLabel> label);
    void stopSmallOnWidget(QPointer<QLabel> label);

private:
    bool isValid(QSharedPointer<QMovie>& animation);

    QSharedPointer<QMovie> animation;
    QSharedPointer<QMovie> small_animation;
};

