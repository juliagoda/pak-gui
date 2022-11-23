#pragma once

#include <QObject>

class ActionsAccessChecker : public QObject
{
    Q_OBJECT
public:
    ActionsAccessChecker();
    void update();

    bool isAspInstalled() const;
    bool isAuracleInstalled() const;
    bool isReflectorInstalled() const;
    bool isGitInstalled() const;
    bool isOnline() const;

signals:
    void aspAccessChanged(bool is_asp_installed);
    void auracleAccessChanged(bool is_auracle_installed);
    void reflectorAccessChanged(bool is_reflector_installed);
    void gitAccessChanged(bool is_git_installed);
    void internetAccessChanged(bool is_online);

private:
    void checkInternetConnection();
    void emitSignals();

    bool is_asp_installed;
    bool is_auracle_installed;
    bool is_reflector_installed;
    bool is_git_installed;
    bool is_online;
};

