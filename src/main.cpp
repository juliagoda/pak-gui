// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of package manager based on "pak" application.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

#include "src/mainwindow.h"
#include "src/settings.h"
#include "src/logger.h"
#include "src/defs.h"

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
#include <QStyleFactory>


int main(int argc, char **argv)
{
    QApplication application(argc, argv);
    QString first_style = QStyleFactory::keys().first();

    if (!Settings::records()->appStyleName().isEmpty())
        first_style = Settings::records()->appStyleName();

    QApplication::setStyle(QStyleFactory::create(first_style));
    KLocalizedString::setApplicationDomain("pak-gui");
    KCrash::initialize();

    KAboutData aboutData( QStringLiteral("pak-gui"),
                          QStringLiteral("pak-gui"),
                          QStringLiteral("1.0"),
                          i18n("Pacman wrapper, AUR and POLAUR helper with Gui (based on \"pak\" application)"),
                          KAboutLicense::GPL_V3,
                          i18n("Copyright 2023, Jagoda \"juliagoda\" Górska"),
                          QLatin1String(),
                          QStringLiteral("https://github.com/juliagoda/pak-gui"),
                          QStringLiteral("https://github.com/juliagoda/pak-gui/issues"));

    aboutData.addAuthor("Jagoda \"juliagoda\" Górska",i18n("Author"), QStringLiteral("juliagoda.pl@protonmail.com"));
    aboutData.setOrganizationDomain("juliagoda.github.com");
    aboutData.setDesktopFileName(QStringLiteral("com.github.juliagoda.pak-gui"));
    aboutData.addLicenseTextFile("LICENSE");

    KAboutData::setApplicationData(aboutData);
    application.setWindowIcon(QIcon::fromTheme(QStringLiteral("pak-gui")));

    Constants constants;
    constants.init();

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
    window->run();
    QObject::connect(window, &MainWindow::closeApp, &application, &QCoreApplication::quit);
    window->show();

    return application.exec();
}
