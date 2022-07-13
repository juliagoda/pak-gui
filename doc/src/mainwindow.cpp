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
#include <KLazyLocalizedString>


MainWindow::MainWindow()
    : KXmlGuiWindow()
{
    mainWindowView = new MainWindowView(this);
    setCentralWidget(mainWindowView);

    KActionCollection* actionCollection = this->actionCollection();
    m_switchAction = actionCollection->addAction(QStringLiteral("switch_action"));
    m_switchAction->setText(i18nc("@action", "Switch Colors"));
    m_switchAction->setIcon(QIcon::fromTheme(QStringLiteral("fill-color")));
    connect(m_switchAction, &QAction::triggered, mainWindowView, &MainWindowView::switchColors);

    KStandardAction::openNew(this, SLOT(fileNew()), actionCollection);
    KStandardAction::quit(qApp, SLOT(closeAllWindows()), actionCollection);
    KStandardAction::preferences(this, SLOT(settingsConfigure()), actionCollection);

    setupGUI();
}

MainWindow::~MainWindow()
{
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