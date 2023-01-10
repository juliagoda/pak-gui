/*
    SPDX-FileCopyrightText: %{CURRENT_YEAR} %{AUTHOR} <%{EMAIL}>

    SPDX-License-Identifier: GPL-2.0-only OR GPL-3.0-only OR LicenseRef-KDE-Accepted-GPL
*/

#include "src/mainwindow.h"
#include "src/settings.h"
#include "src/logger.h"

#include <KCrash>
#include <KDBusService>
#include <KAboutData>
#include <KLocalizedString>

#include <QApplication>
#include <QCommandLineParser>
#include <QIcon>
#include <QLoggingCategory>
#include <QTextCodec>
#include <QLoggingCategory>
#include <QResource>
#include <QDir>

int main(int argc, char **argv)
{
    QApplication application(argc, argv);

    KLocalizedString::setApplicationDomain("pak-gui");
    KCrash::initialize();

    KAboutData aboutData( QStringLiteral("pak-gui"),
                          i18n("pak-gui"),
                          QStringLiteral("1.0"),
                          i18n("Pacman wrapper, AUR and POLAUR helper with Gui"),
                          KAboutLicense::GPL_V3,
                          i18n("Copyright 2022, Jagoda \"juliagoda\" Górska"),
                          QLatin1String(),
                          QStringLiteral("https://github.com/CachyOS/pak-gui"),
                          QStringLiteral("https://github.com/CachyOS/pak-gui/issues"));

    aboutData.addAuthor(i18n("Jagoda \"juliagoda\" Górska"),i18n("Author"), QStringLiteral("juliagoda.pl@protonmail.com"));
    aboutData.setOrganizationDomain("CachyOS.github.com");
    aboutData.setDesktopFileName(QStringLiteral("com.github.CachyOS.pak-gui"));
    aboutData.addLicenseTextFile("LICENSE");

    KAboutData::setApplicationData(aboutData);
    application.setWindowIcon(QIcon::fromTheme(QStringLiteral("pak-gui")));

    QCommandLineParser parser;
    aboutData.setupCommandLine(&parser);

    parser.process(application);
    aboutData.processCommandLine(&parser);

    KDBusService appDBusService(KDBusService::Multiple | KDBusService::NoExitOnFailure);

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);

    QString config_path = Settings::records()->logsFilePath();
    if (!QDir().exists(config_path) &&
        !QDir().mkpath(config_path))
           Logger::logger()->logWarning(QStringLiteral("Path %1 couldn't be created!").arg(config_path));

    QPointer<MainWindow> window = new MainWindow;
    QObject::connect(window, &MainWindow::closeApp, &application, &QCoreApplication::quit);
    window->show();

    return application.exec();
}
