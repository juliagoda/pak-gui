#include "spinninganimation.h"
#include "logger.h"

SpinningAnimation::SpinningAnimation() :
    animation(new QMovie(":/waiting.gif"), &QObject::deleteLater)
{

}

void SpinningAnimation::changeToSmallSize()
{
    if (isValid())
        animation->setFileName(":/waiting-small.gif");
}


void SpinningAnimation::changeToBiggerSize()
{
    if (isValid())
        animation->setFileName(":/waiting.gif");
}


void SpinningAnimation::startOnMainWidgets(QPointer<QLabel> first_label,
                                           QPointer<QLabel> second_label,
                                           QPointer<QLabel> third_label)
{
    if (animation.isNull())
        return;

    animation->setFileName(":/waiting.gif");
    first_label->setMovie(animation.get());
    first_label->show();
    second_label->setMovie(animation.get());
    second_label->show();
    third_label->setMovie(animation.get());
    third_label->show();
    animation->start();
    Logger::logger()->logDebug(QStringLiteral("Animation started!"));
}


void SpinningAnimation::startOnWidget(QPointer<QLabel> label)
{
    if (animation.isNull())
        return;

    label->setMovie(animation.get());
    label->show();
    animation->start();
    Logger::logger()->logDebug(QStringLiteral("Animation started!"));
}


void SpinningAnimation::stopOnWidget(QPointer<QLabel> label)
{
    if (animation.isNull())
        return;

    label->hide();
    animation->stop();
    Logger::logger()->logDebug(QStringLiteral("Animation stopped!"));
}


void SpinningAnimation::startOnWidgetWithChangeToSmall(QPointer<QLabel> label)
{
    changeToSmallSize();
    startOnWidget(label);
}


void SpinningAnimation::startOnWidgetWithChangeToBigger(QPointer<QLabel> label)
{
    changeToBiggerSize();
    startOnWidget(label);
}


bool SpinningAnimation::isValid()
{
    if (animation.isNull() || animation->state() == QMovie::MovieState::Running)
    {
        Logger::logger()->logDebug("Cannot toggle animation - animation is running or not exists");
        return false;
    }

    return true;
}
