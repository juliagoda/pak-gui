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

public Q_SLOTS:
    void startSmallOnWidget(QPointer<QLabel> label);
    void stopSmallOnWidget(QPointer<QLabel> label);

private:
    bool isValid(QSharedPointer<QMovie>& animation);

    QSharedPointer<QMovie> animation;
    QSharedPointer<QMovie> small_animation;
};

