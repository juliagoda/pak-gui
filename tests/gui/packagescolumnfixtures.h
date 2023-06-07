// Copyright (C) 2023 Jagoda "juliagoda" Górska
//
// This file is part of tests for CachyOS package manager (based on "pak" application).
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

#pragma once

#include "mainwindow.h"
#include "mainwindowview.h"
#include "checkpackage.h"
#include "qipackage.h"
#include "sipackage.h"


#include <QAction>
#include <QString>
#include <QWidget>


const QString package_content_a52dec = "Name            : a52dec\n"
                                       "Version         : 0.7.4-12.1\n"
                                       "Description     : A free library for decoding ATSC A/52 streams\n"
                                       "Architecture    : x86_64\n"
                                       "URL             : http://liba52.sourceforge.net/\n"
                                       "Licenses        : GPL2\n"
                                       "Groups          : None\n"
                                       "Provides        : None\n"
                                       "Depends On      : glibc\n"
                                       "Optional Deps   : None\n"
                                       "Required By     : gst-plugins-ugly  mplayer  vlc\n"
                                       "Optional For    : None\n"
                                       "Conflicts With  : None\n"
                                       "Replaces        : None\n"
                                       "Installed Size  : 130,58 KiB\n"
                                       "Packager        : ALHP x86-64-v3 <alhp@harting.dev>\n"
                                       "Build Date      : wto, 27 gru 2022, 01:30:08\n"
                                       "Install Date    : pon, 2 sty 2023, 13:19:58\n"
                                       "Install Reason  : Installed as a dependency for another package\n"
                                       "Install Script  : No\n"
                                       "Validated By    : Signature\n";

const QString package_content_gimp = "Name            : gimp\n"
                                     "Version         : 2.10.32-3.1\n"
                                     "Description     : GNU Image Manipulation Program\n"
                                     "Architecture    : x86_64\n"
                                     "URL             : https://www.gimp.org/\n"
                                     "Licenses        : GPL  LGPL\n"
                                     "Groups          : None\n"
                                     "Provides        : None\n"
                                     "Depends On      : babl  dbus-glib  desktop-file-utils  gegl  glib-networking  hicolor-icon-theme  openjpeg2  lcms2  libheif  libexif  libgudev  libmng  libmypaint  librsvg  libwebp  libwmf  libxmu  libxpm  mypaint-brushes1  openexr\n"
                                                       "poppler-data  gtk2  graphviz\n"
                                     "Optional Deps   : gutenprint: for sophisticated printing only as gimp has built-in cups print support\n"
                                                       "poppler-glib: for pdf support [installed]\n"
                                                       "alsa-lib: for MIDI event controller module [installed]\n"
                                                       "curl: for URI support [installed]\n"
                                                       "ghostscript: for postscript support [installed]\n"
                                                       "gvfs: for HTTP/S support (and many other schemes) [installed]\n"
                                     "Required By     : None\n"
                                     "Optional For    : None\n"
                                     "Conflicts With  : gimp-plugin-wavelet-decompose\n"
                                     "Replaces        : gimp-plugin-wavelet-decompose\n"
                                     "Installed Size  : 116,73 MiB\n"
                                     "Packager        : ALHP x86-64-v3 <alhp@harting.dev>\n"
                                     "Build Date      : czw, 5 sty 2023, 05:24:56\n"
                                     "Install Date    : śro, 11 sty 2023, 22:43:53\n"
                                     "Install Reason  : Explicitly installed\n"
                                     "Install Script  : Yes\n"
                                     "Validated By    : Signature\n";

const QString package_content_a52dec_si = "Repository      : cachyos-v3\n"
                                          "Name            : a52dec\n"
                                          "Version         : 0.7.4-12.1\n"
                                          "Description     : A free library for decoding ATSC A/52 streams\n"
                                          "Architecture    : x86_64\n"
                                          "URL             : http://liba52.sourceforge.net/\n"
                                          "Licenses        : GPL2\n"
                                          "Groups          : None\n"
                                          "Provides        : None\n"
                                          "Depends On      : glibc\n"
                                          "Optional Deps   : None\n"
                                          "Conflicts With  : None\n"
                                          "Replaces        : None\n"
                                          "Download Size   : 45,72 KiB\n"
                                          "Installed Size  : 126,58 KiB\n"
                                          "Packager        : CachyOS <admin@cachyos.org>\n"
                                          "Build Date      : wto, 27 gru 2022, 11:04:37\n"
                                          "Validated By    : MD5 Sum  SHA-256 Sum  Signature\n";

const QString packages_to_update_content_binutils = "binutils                        2.40-1.1 => 2.40-2.1";
const QString packages_to_update_content_ddrescue = "ddrescue                        1.26-1.1 => 1.27-1.1";
const QString packages_to_update_content_fwupd = "fwupd                           1.8.9-2.1 => 1.8.10-1.1";
const QString packages_to_update_content_konsole = "repo-refreshed/konsole          22.12.1-1.1 => 22.12.1-1.2";


const QString package_content_alsa_utils = "Name            : alsa-utils\n"
                                           "Version         : 1.2.8-1.1\n"
                                           "Description     : Advanced Linux Sound Architecture - Utilities\n"
                                           "Architecture    : x86_64\n"
                                           "URL             : https://www.alsa-project.org\n"
                                           "Licenses        : GPL2\n"
                                           "Groups          : None\n"
                                           "Provides        : None\n"
                                           "Depends On      : glibc  pciutils  psmisc  libasound.so=2-64\n"
                                           "                  libatopology.so=2-64  libformw.so=6-64  libmenuw.so=6-64\n"
                                           "                  libncursesw.so=6-64  libpanelw.so=6-64  libsamplerate.so=0-64\n"
                                           "Optional Deps   : fftw: for alsabat [installed]\n"
                                           "Required By     : None\n"
                                           "Optional For    : None\n"
                                           "Conflicts With  : None\n"
                                           "Replaces        : None\n"
                                           "Installed Size  : 2,34 MiB\n"
                                           "Packager        : ALHP x86-64-v3 <alhp@harting.dev>\n"
                                           "Build Date      : pią, 28 paź 2022, 11:01:32\n"
                                           "Install Date    : pon, 31 paź 2022, 18:26:51\n"
                                           "Install Reason  : Explicitly installed\n"
                                           "Install Script  : No\n";

const QString package_content_alsa_utils_si = "Repository      : extra-x86-64-v3\n"
                                              "Name            : alsa-utils\n"
                                              "Version         : 1.2.8-1.1\n"
                                              "Description     : Advanced Linux Sound Architecture - Utilities\n"
                                              "Architecture    : x86_64\n"
                                              "URL             : https://www.alsa-project.org\n"
                                              "Licenses        : GPL2\n"
                                              "Groups          : None\n"
                                              "Provides        : None\n"
                                              "Depends On      : glibc  pciutils  psmisc  libasound.so=2-64  libatopology.so=2-64  libformw.so=6-64  libmenuw.so=6-64  libncursesw.so=6-64  libpanelw.so=6-64  libsamplerate.so=0-64\n"
                                              "Optional Deps   : fftw: for alsabat\n"
                                              "Conflicts With  : None\n"
                                              "Replaces        : None\n"
                                              "Download Size   : 1204,11 KiB\n"
                                              "Installed Size  : 2394,16 KiB\n"
                                              "Packager        : ALHP x86-64-v3 <alhp@harting.dev>\n"
                                              "Build Date      : pią, 28 paź 2022, 11:01:32\n"
                                              "Validated By    : MD5 Sum  SHA-256 Sum  Signature\n";


const QString defaultStylesheet = "color: white;\nbackground-color: black;\nfont-family: Lucida Console,Lucida Sans Typewriter,monaco,Bitstream Vera Sans Mono,monospace;\npadding: 3px;";


class MockMainWindowView : public MainWindowView
{
public:
    MockMainWindowView(QWidget* new_widget) :
        MainWindowView(new_widget)
    {
        // ...
    }

    void checkUpdates() override
    {
        // ...
    }

    void run() override
    {
        // ...
    }

    void showFinishInformation() override
    {
        // ...
    }

    friend class TestInstalledPackagesColumn;
    friend class TestAvailablePackagesColumn;
    friend class TestUpdatedPackagesColumn;
    friend class TestMainWindow;
    friend class MainWindowViewGuiTest;
    friend class TestSettingsWindow;
    friend class SettingsTest;
};


class MockProcess : public Process
{
public:
    MockProcess(QSharedPointer<ActionsAccessChecker>& new_actions_access_checker, QWidget* new_parent) :
        Process(new_actions_access_checker, new_parent)
    {
        // ...
    }

    ~MockProcess() override = default;

    void startProcess(Task new_task) override
    {
        QString line = "Cache directory: /var/cache/pacman/pkg/\n";
        processReadLine(line, new_task);
    }

    bool askQuestion(Task new_task, QStringList new_checked_packages) override
    {
        Q_UNUSED(new_task)
        Q_UNUSED(new_checked_packages)
        return true;
    }
};


class MockMainWindow : public MainWindow
{
public:
    MockMainWindow() :
        MainWindow()
    {

    }

    void run() override
    {
        initSignals();
        setupGUI(Default, "pak-gui.rc");
        setXMLFile("pak-gui.rc");
    }

    void triggerDownloadPackageAction()
    {
        download_action.data()->trigger();
    }

    void triggerSearchPackageAction()
    {
        search_action.data()->trigger();
    }

    void triggerShowStatisticsWindow()
    {
        print_statistics_action.data()->trigger();
    }

    friend class TestMainWindow;
    friend class MainWindowViewGuiTest;
    friend class TestSettingsWindow;
    friend class SettingsTest;
};


class MockCheckPackage : public CheckPackage
{
public:
    explicit MockCheckPackage(QString package_content,
                              Package::Source new_source) :
        CheckPackage(package_content, new_source)
    {}

    ~MockCheckPackage() override = default;

    friend class TestCheckPackage;
};


class MockQiPackage : public QiPackage
{
public:
    explicit MockQiPackage(QString& package_content) :
        QiPackage(package_content)
    {}

    friend class TestQiPackage;
};


class MockSiPackage : public SiPackage
{
public:
    explicit MockSiPackage(QString& package_content) :
        SiPackage(package_content)
    {}

    friend class TestSiPackage;
};
