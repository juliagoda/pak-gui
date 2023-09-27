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

    template<int> void startOnWidget(const QPointer<QLabel>& label);
    template<int> void stopOnWidget(const QPointer<QLabel>& label);
    void startOnMainWidgets(const QPointer<QLabel>& first_label,
                            const QPointer<QLabel>& second_label,
                            const QPointer<QLabel>& third_label);
    void stopOnMainWidgets(const QPointer<QLabel>& first_label,
                           const QPointer<QLabel>& second_label,
                           const QPointer<QLabel>& third_label);
    bool isAnimationRunning() const;
    bool isSmallAnimationRunning() const;

public Q_SLOTS:
    void startSmallOnWidget(const QPointer<QLabel>& label);
    void stopSmallOnWidget(const QPointer<QLabel>& label);

private:
    bool isValid(const QScopedPointer<QMovie>& animation);
    void restartMovie(const QPointer<QLabel>& first_label,
                      const QScopedPointer<QMovie>& animation);

    QScopedPointer<QMovie> animation;
    QScopedPointer<QMovie> animation2;
    QScopedPointer<QMovie> animation3;
    QScopedPointer<QMovie> small_animation;
};

