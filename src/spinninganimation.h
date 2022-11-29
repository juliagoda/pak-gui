#pragma once

#include <QMovie>
#include <QSharedPointer>
#include <QLabel>


class SpinningAnimation
{
public:
    explicit SpinningAnimation();
    void changeToSmallSize();
    void changeToBiggerSize();
    void startOnWidget(QPointer<QLabel> label);
    void stopOnWidget(QPointer<QLabel> label);
    void startOnMainWidgets(QPointer<QLabel> first_label,
                            QPointer<QLabel> second_label,
                            QPointer<QLabel> third_label);

public Q_SLOTS:
    void startOnWidgetWithChangeToSmall(QPointer<QLabel> label);
    void startOnWidgetWithChangeToBigger(QPointer<QLabel> label);

private:
    bool isValid();

    QSharedPointer<QMovie> animation;
};

