#include "spinninganimation.h"

#include "logger.h"

SpinningAnimation::SpinningAnimation() :
    animation(new QMovie(":/waiting.gif"), &QObject::deleteLater),
    small_animation(new QMovie(":/waiting-small.gif"), &QObject::deleteLater)
{

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
