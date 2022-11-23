/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// application headers
#include "mainwindow.h"

#include "mainwindowview.h"

#include <QAction>

// KF headers
#include <KActionCollection>
#include <KConfigDialog>
#include <KLocalizedString>
#include <KStandardAction>

// within statusbar (or other place) add diodes (green for available packages places - (AUR for example after package detection), red otherwise)
MainWindow::MainWindow()
    : KXmlGuiWindow(),
      process(QSharedPointer<Process>(new Process))
{
    mainWindowView = new MainWindowView(process, this);
    setCentralWidget(mainWindowView);

    KActionCollection* actionCollection = this->actionCollection();

    m_updateAction = new QAction(this);
    m_updateAction->setText(i18n("&Update"));
    m_updateAction->setIcon(QIcon::fromTheme("update"));
    actionCollection->setDefaultShortcut(m_updateAction, Qt::CTRL + Qt::Key_U);
    actionCollection->addAction("update", m_updateAction);
    connect(m_updateAction, &QAction::triggered, this, [this]() { process->run(Process::Task::UpdateInstalledPackages); }, Qt::AutoConnection);

    m_refreshAction = new QAction(this);
    m_refreshAction->setText(i18n("&Refresh"));
    m_refreshAction->setIcon(QIcon::fromTheme("refresh"));
    actionCollection->setDefaultShortcut(m_refreshAction, Qt::CTRL + Qt::Key_R);
    actionCollection->addAction("refresh", m_refreshAction);
    connect(m_refreshAction, &QAction::triggered, mainWindowView, &MainWindowView::refresh);
    connect(mainWindowView, &MainWindowView::initStarted, this, &MainWindow::disableActions);
    connect(mainWindowView, &MainWindowView::initEnded, this, &MainWindow::enableActions);

    m_downloadAction = new QAction(this);
    m_downloadAction->setText(i18n("&Download"));
    m_downloadAction->setIcon(QIcon::fromTheme("download"));
    actionCollection->setDefaultShortcut(m_downloadAction, Qt::CTRL + Qt::Key_D);
    actionCollection->addAction("download", m_downloadAction);
    connect(m_downloadAction, &QAction::triggered, mainWindowView, &MainWindowView::downloadPackage);

    m_updateAllAction = new QAction(this);
    m_updateAllAction->setText(i18n("&Update all packages"));
    m_updateAllAction->setIcon(QIcon::fromTheme("updateAllPackages"));
    actionCollection->setDefaultShortcut(m_updateAllAction, Qt::CTRL + Qt::Key_U + Qt::Key_A);
    actionCollection->addAction("updateAllPackages", m_updateAllAction);
    connect(m_updateAllAction, &QAction::triggered, this, [this]() { process->run(Process::Task::UpdateAll); }, Qt::AutoConnection);

    m_updateMirrorsAction = new QAction(this);
    m_updateMirrorsAction->setText(i18n("&Update mirrors"));
    m_updateMirrorsAction->setIcon(QIcon::fromTheme("updateMirrors"));
    actionCollection->setDefaultShortcut(m_updateMirrorsAction, Qt::CTRL + Qt::Key_U + Qt::Key_M);
    actionCollection->addAction("updateMirrors", m_updateMirrorsAction);
    connect(m_updateMirrorsAction, &QAction::triggered, this, [this]() { process->run(Process::Task::MirrorsUpdate); }, Qt::AutoConnection);

    m_cleanAction = new QAction(this);
    m_cleanAction->setText(i18n("&Clear"));
    m_cleanAction->setIcon(QIcon::fromTheme("clear"));
    actionCollection->setDefaultShortcut(m_cleanAction, Qt::CTRL + Qt::Key_C);
    actionCollection->addAction(i18n("clear"), m_cleanAction);
    connect(m_cleanAction, &QAction::triggered, this, [this]() { process->run(Process::Task::Clean); }, Qt::AutoConnection);

    m_undoAction = actionCollection->addAction(QStringLiteral("undo"));
    m_undoAction->setText(i18nc("@action", "Undo"));
    m_undoAction->setIcon(QIcon::fromTheme(QStringLiteral("undo")));
    //connect(m_undoAction, &QAction::triggered, mainWindowView, &MainWindowView::switchColors);

    // action - statistics part:
    m_printStatisticsAction = new QAction(this);
    m_printStatisticsAction->setText(i18n("&Statistics"));
    m_printStatisticsAction->setIcon(QIcon::fromTheme("statistics"));
    actionCollection->setDefaultShortcut(m_printStatisticsAction, Qt::CTRL + Qt::Key_S);
    actionCollection->addAction("statistics", m_printStatisticsAction);
    connect(m_printStatisticsAction, &QAction::triggered, mainWindowView, &MainWindowView::showStatisticsWindow);

    // action - vcs part:
    m_printVCSPackagesAction = new QAction(this);
    m_printVCSPackagesAction->setText(i18n("&Installed vcs packages"));
    m_printVCSPackagesAction->setIcon(QIcon::fromTheme("installedVcsPackages"));
    actionCollection->setDefaultShortcut(m_printVCSPackagesAction, Qt::CTRL + Qt::Key_P);
    actionCollection->addAction("installedVcsPackages", m_printVCSPackagesAction);
    connect(m_printVCSPackagesAction, &QAction::triggered, this, [this]() { process->run(Process::Task::PrintVCSPackages); }, Qt::AutoConnection);

    disableActions();

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
    m_downloadAction->setDisabled(false);
    m_updateAllAction->setDisabled(false);
    m_updateMirrorsAction->setDisabled(false);
    m_cleanAction->setDisabled(false);
    m_undoAction->setDisabled(false);
    m_printStatisticsAction->setDisabled(false);
    m_printVCSPackagesAction->setDisabled(false);
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
