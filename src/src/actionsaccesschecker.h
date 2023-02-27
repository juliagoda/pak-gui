#pragma once

#include <QObject>
#include <QMutex>


class ActionsAccessChecker : public QObject
{
    Q_OBJECT

public:
    static ActionsAccessChecker* actionsAccessChecker(QWidget* new_parent);
    virtual ~ActionsAccessChecker() override;
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
    virtual void showRequiredPackagesNotFoundWindow(const QStringList& not_installed_packages) const;
    void findRequiredPackages();
    void updateIsOnline(bool new_is_online);
    void emitSignals();

    virtual bool checkNetworkInterfaces() const;
    bool findPackage(const QString& package_name);
    QStringList getNotInstalledPackagesList();

private:
    bool is_asp_installed = false;
    bool is_auracle_installed = false;
    bool is_reflector_installed = false;
    bool is_git_installed = false;
    bool is_online = true;
    QWidget* parent = nullptr;

    static QStringList required_packages;
    static ActionsAccessChecker* instance;
    static QMutex mutex;
};

