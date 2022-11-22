/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// application headers
#include "mainwindow.h"

#include "mainwindowview.h"

// KF headers
#include <KActionCollection>
#include <KConfigDialog>
#include <KLocalizedString>

// within statusbar (or other place) add diodes (green for available packages places - (AUR for example after package detection), red otherwise)
MainWindow::MainWindow()
    : KXmlGuiWindow(),
      process(QSharedPointer<Process>(new Process))
{
    mainWindowView = new MainWindowView(process, this);
    setCentralWidget(mainWindowView);
    //actionCollection()->setDefaultShortcut(updateAction, Qt::CTRL + Qt::Key_U);

    KActionCollection* actionCollection = this->actionCollection();

    m_updateAction = actionCollection->addAction(QStringLiteral("update"));
    m_updateAction->setText(i18nc("@action", "Update"));
    m_updateAction->setIcon(QIcon::fromTheme(QStringLiteral("update")));
    connect(m_updateAction, &QAction::triggered, this, [this]() { process->run(Process::Task::UpdateInstalledPackages); }, Qt::AutoConnection);

    m_refreshAction = actionCollection->addAction(QStringLiteral("refresh"));
    m_refreshAction->setText(i18nc("@action", "Refresh"));
    m_refreshAction->setIcon(QIcon::fromTheme(QStringLiteral("refresh")));
    connect(m_refreshAction, &QAction::triggered, mainWindowView, &MainWindowView::refresh);
    connect(mainWindowView, &MainWindowView::initStarted, this, &MainWindow::disableActions);
    connect(mainWindowView, &MainWindowView::initEnded, this, &MainWindow::enableActions);

    // action - AUR part:  list of flags used to manage AUR packages
    m_searchAction = actionCollection->addAction(QStringLiteral("search"));
    m_searchAction->setText(i18nc("@action", "Search"));
    m_searchAction->setIcon(QIcon::fromTheme(QStringLiteral("search")));
    //connect(m_searchAction, &QAction::triggered, mainWindowView, &MainWindowView::switchColors);

    // action - download part:  pak is able to download PKGBUILDs of official packages (asp) and AUR PKGBUILDs (git)
    m_downloadAction = actionCollection->addAction(QStringLiteral("download"));
    m_downloadAction->setText(i18nc("@action", "Download"));
    m_downloadAction->setIcon(QIcon::fromTheme(QStringLiteral("download")));
    connect(m_downloadAction, &QAction::triggered, mainWindowView, &MainWindowView::downloadPackage);

    m_updateAllAction = actionCollection->addAction(QStringLiteral("update_all_packages"));
    m_updateAllAction->setText(i18nc("@action", "Update all"));
    m_updateAllAction->setIcon(QIcon::fromTheme(QStringLiteral("update_all_packages")));
    connect(m_updateAllAction, &QAction::triggered, this, [this]() { process->run(Process::Task::UpdateAll); }, Qt::AutoConnection);

    m_updateMirrorsAction = actionCollection->addAction(QStringLiteral("update_mirrors"));
    m_updateMirrorsAction->setText(i18nc("@action", "Update mirrors"));
    m_updateMirrorsAction->setIcon(QIcon::fromTheme(QStringLiteral("update_mirrors")));
    connect(m_updateMirrorsAction, &QAction::triggered, this, [this]() { process->run(Process::Task::MirrorsUpdate); }, Qt::AutoConnection);

    m_cleanAction = actionCollection->addAction(QStringLiteral("clean"));
    m_cleanAction->setText(i18nc("@action", "Clean"));
    m_cleanAction->setIcon(QIcon::fromTheme(QStringLiteral("clean")));
    connect(m_cleanAction, &QAction::triggered, this, [this]() { process->run(Process::Task::Clean); }, Qt::AutoConnection);

    m_undoAction = actionCollection->addAction(QStringLiteral("undo"));
    m_undoAction->setText(i18nc("@action", "Undo"));
    m_undoAction->setIcon(QIcon::fromTheme(QStringLiteral("undo")));
    //connect(m_undoAction, &QAction::triggered, mainWindowView, &MainWindowView::switchColors);

    // action - statistics part:
    m_printStatisticsAction = actionCollection->addAction(QStringLiteral("statistics"));
    m_printStatisticsAction->setText(i18nc("@action", "Statistics"));
    m_printStatisticsAction->setIcon(QIcon::fromTheme(QStringLiteral("statistics")));
    connect(m_printStatisticsAction, &QAction::triggered, mainWindowView, &MainWindowView::showStatisticsWindow);

    // action - vcs part:
    m_printVCSPackagesAction = actionCollection->addAction(QStringLiteral("installed_vcs_packages"));
    m_printVCSPackagesAction->setText(i18nc("@action", "Installed vcs packages"));
    m_printVCSPackagesAction->setIcon(QIcon::fromTheme(QStringLiteral("installed_vcs_packages")));
    connect(m_printVCSPackagesAction, &QAction::triggered, this, [this]() { process->run(Process::Task::PrintVCSPackages); }, Qt::AutoConnection);

    disableActions();

    KStandardAction::openNew(this, SLOT(fileNew()), actionCollection);
    KStandardAction::quit(qApp, SLOT(closeAllWindows()), actionCollection);
    KStandardAction::preferences(this, SLOT(settingsConfigure()), actionCollection);

    setupGUI(Default, "pak-gui.rc");
    setXMLFile("pak-gui.rc");
}

MainWindow::~MainWindow()
{

}


void MainWindow::disableActions()
{
    m_updateAction->setDisabled(true);
    m_refreshAction->setDisabled(true);
    m_searchAction->setDisabled(true);
    m_downloadAction->setDisabled(true);
    m_updateAllAction->setDisabled(true);
    m_updateMirrorsAction->setDisabled(true);
    m_cleanAction->setDisabled(true);
    m_undoAction->setDisabled(true);
    m_printStatisticsAction->setDisabled(true);
    m_printVCSPackagesAction->setDisabled(true);
}


void MainWindow::enableActions()
{
    m_updateAction->setDisabled(false);
    m_refreshAction->setDisabled(false);
    m_searchAction->setDisabled(false);
    m_downloadAction->setDisabled(false);
    m_updateAllAction->setDisabled(false);
    m_updateMirrorsAction->setDisabled(false);
    m_cleanAction->setDisabled(false);
    m_undoAction->setDisabled(false);
    m_printStatisticsAction->setDisabled(false);
    m_printVCSPackagesAction->setDisabled(false);
}


void MainWindow::fileNew()
{
    (new MainWindow)->show();
}


void MainWindow::settingsConfigure()
{
    // The preference dialog is derived from prefs_base.ui
    //
    // compare the names of the widgets in the .ui file
    // to the names of the variables in the .kcfg file
    //avoid to have 2 dialogs shown
    if (KConfigDialog::showDialog(QStringLiteral("settings"))) {
        return;
    }

    KConfigDialog *dialog = new KConfigDialog(this, QStringLiteral("settings"), pakGuiSettings::self());
    QWidget *generalSettingsPage = new QWidget;
    m_settings.setupUi(generalSettingsPage);
    dialog->addPage(generalSettingsPage, i18nc("@title:tab", "General"), QStringLiteral("package_setting"));
    connect(dialog, &KConfigDialog::settingsChanged, mainWindowView, &MainWindowView::handleSettingsChanged);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}
