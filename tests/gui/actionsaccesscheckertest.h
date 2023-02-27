#pragma once

#include "actionsaccesschecker.h"

#include <QApplication>
#include <QtTest/QtTest>
#include <QWidget>


class MockActionsAccessChecker : public ActionsAccessChecker
{
    Q_OBJECT

public:
    explicit MockActionsAccessChecker(QWidget* new_parent);
    ~MockActionsAccessChecker() override = default;
    friend class TestActionsAccessChecker;
    void showRequiredPackagesNotFoundWindow(const QStringList& not_installed_packages) const override;
    bool checkNetworkInterfaces() const override;
};




class TestActionsAccessChecker : public QObject
{
    Q_OBJECT

public:
    TestActionsAccessChecker(QObject* parent = nullptr);

private slots:
    void internetConnectionStateSignalEmittedAfterChange();
    void stopApplicationSendSignalAfterNotFindingRequiredPackages();
    void initiallyPackagesAreNotFound();
    void initiallyInternetConnectionIsOn();
    void properlyFindsExecutableFileWithExampleOfPakQtests();
    void emitSignalFunctionContainsEmitsForFourPackages();
    void cleanup();

private:
    MockActionsAccessChecker actions_access_checker;
};


