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
#include <QTextCodec>


int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    KLocalizedString::setApplicationDomain("pak-gui");
    KCrash::initialize();

    KAboutData aboutData( QStringLiteral("pak-gui"),
                          i18n("pak-gui"),
                          QStringLiteral("1.0"),
                          i18n("Pacman wrapper, AUR and POLAUR helper with Gui"),
                          KAboutLicense::GPL,
                          i18n("Copyright 2022, Jagoda \"juliagoda\" Górska"));

    aboutData.addAuthor(i18n("Jagoda \"juliagoda\" Górska"),i18n("Author"), QStringLiteral("juliagoda.pl@protonmail.com"));
    aboutData.setOrganizationDomain("CachyOS.github.com");
    aboutData.setDesktopFileName(QStringLiteral("com.github.CachyOS.pak-gui"));

    KAboutData::setApplicationData(aboutData);
    application.setWindowIcon(QIcon::fromTheme(QStringLiteral("pak-gui")));

    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);

    parser.process(application);
    aboutData.processCommandLine(&parser);

    KDBusService appDBusService(KDBusService::Multiple | KDBusService::NoExitOnFailure);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    MainWindow *window = new MainWindow;
    window->show();

    return application.exec();
}
