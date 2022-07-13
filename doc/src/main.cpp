/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

// application header
#include "mainwindow.h"

// KF headers
#include <KCrash>
#include <KDBusService>
#include <KAboutData>
#include <KLocalizedString>

// Qt headers
#include <QApplication>
#include <QCommandLineParser>
#include <QIcon>
#include <QLoggingCategory>


int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    KLocalizedString::setApplicationDomain("pak-gui");
    KCrash::initialize();

    KAboutData aboutData( QStringLiteral("pak-gui"),
                          i18n("pak-gui"),
                          QStringLiteral("%{VERSION}"),
                          i18n("A Simple Application written with KDE Frameworks"),
                          KAboutLicense::GPL,
                          i18n("Copyright %{CURRENT_YEAR}, %{AUTHOR} <%{EMAIL}>"));

    aboutData.addAuthor(i18n("%{AUTHOR}"),i18n("Author"), QStringLiteral("%{EMAIL}"));
    aboutData.setOrganizationDomain("example.org");
    aboutData.setDesktopFileName(QStringLiteral("org.example.pak-gui"));

    KAboutData::setApplicationData(aboutData);
    application.setWindowIcon(QIcon::fromTheme(QStringLiteral("pak-gui")));

    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);

    parser.process(application);
    aboutData.processCommandLine(&parser);

    KDBusService appDBusService(KDBusService::Multiple | KDBusService::NoExitOnFailure);

    MainWindow *window = new MainWindow;
    window->show();

    return application.exec();
}
