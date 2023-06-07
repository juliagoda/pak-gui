// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of CachyOS package manager based on "pak" application.
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
                          QStringLiteral("pak-gui"),
                          QStringLiteral("1.0"),
                          i18n("Pacman wrapper, AUR and POLAUR helper with Gui"),
                          KAboutLicense::GPL_V3,
                          i18n("Copyright 2023, Jagoda \"juliagoda\" Górska"),
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

    QString codec = "UTF-8";
    QString locale = std::locale("").name().c_str();
    QString lcName = "LC_NAME=";
    auto in = locale.indexOf(lcName);
    auto out = locale.indexOf(";", in);
    auto result = locale.mid(in + lcName.size(), out - (in + lcName.size()));

    codec = result.split(".").back();

    QTextCodec::setCodecForLocale(QTextCodec::codecForName(codec.toStdString().c_str()));
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
