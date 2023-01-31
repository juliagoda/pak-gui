#pragma once

#include "mainwindowview.h"

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
                                       "Install Script  : No\n";

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
    Q_OBJECT

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
};


class MockProcess : public Process
{
    Q_OBJECT

public:
    MockProcess(QSharedPointer<ActionsAccessChecker>& new_actions_access_checker, QWidget* new_parent) :
        Process(new_actions_access_checker, new_parent)
    {
        // ...
    }

    void startProcess(Task new_task) override
    {
        Q_UNUSED(new_task)
    }
};
