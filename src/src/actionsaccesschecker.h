#pragma once

#include <QObject>
#include <QMutex>

class ActionsAccessChecker : public QObject
{
    Q_OBJECT

public:
    static ActionsAccessChecker* actionsAccessChecker(QWidget* new_parent);
    ~ActionsAccessChecker() override;
    ActionsAccessChecker(ActionsAccessChecker& instance) = delete;
    void operator=(const ActionsAccessChecker& instance) = delete;

    bool isAspInstalled() const;
    bool isAuracleInstalled() const;
    bool isReflectorInstalled() const;
    bool isGitInstalled() const;
    bool isOnline() const;

public Q_SLOTS:
    void checkRequiredPackages();
    void checkInternetConnection();

signals:
    void aspAccessChanged(bool is_asp_installed);
    void auracleAccessChanged(bool is_auracle_installed);
    void reflectorAccessChanged(bool is_reflector_installed);
    void gitAccessChanged(bool is_git_installed);
    void internetAccessChanged(bool is_online);
    void requiredPackagesNotFound();

protected:
    explicit ActionsAccessChecker(QWidget* new_parent);
    static void fillRequiredPackagesList(const QStringList& required_packages);
    QStringList getNotInstalledPackagesList();
    void findRequiredPackages();
    virtual void showRequiredPackagesNotFoundWindow(const QStringList& not_installed_packages);
    bool findPackage(const QString& package_name);
    virtual bool checkNetworkInterfaces();

private:
    void emitSignals();

    static QStringList required_packages;
    bool is_asp_installed = false;
    bool is_auracle_installed = false;
    bool is_reflector_installed = false;
    bool is_git_installed = false;
    bool is_online = true;
    QWidget* parent;

    static ActionsAccessChecker* instance;
    static QMutex mutex;
};

