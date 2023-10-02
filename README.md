# ![Browse](https://raw.githubusercontent.com/juliagoda/pak-gui/main/resources/icons/app/64-apps-pak-gui.png) pak-gui

pak-gui is a pacman wrapper, AUR and POLAUR helper of [Damian N](https://gitlab.com/nycko123/pak) enhanced with GUI.

[![pak-gui](https://github.com/juliagoda/pak-gui/actions/workflows/cmake-single-platform.yml/badge.svg?branch=main)](https://github.com/juliagoda/pak-gui/actions/workflows/cmake-single-platform.yml)
[![CodeFactor](https://www.codefactor.io/repository/github/juliagoda/pak-gui/badge)](https://www.codefactor.io/repository/github/juliagoda/pak-gui)


<br/>

1. [Installing from source](#installing-from-source)
   1. [Required dependencies with Qt5](#required-dependencies-with-qt5)
   2. [Optional dependencies](#optional-dependencies)
   3. [Configuration](#configuration)
   4. [Installation](#installation)
3. [Installation from PKGBUILD](#installation-from-pkgbuild)
4. [Running tests with sources](#running-tests-with-sources)  
5. [Package remove](#package-remove)
   1. [Sources](#sources)
   2. [PKGBUILD](#pkgbuild)
7. [Attention](#attention)  

<br/>

## Installing from source

### Required dependencies with Qt5

- cmake
- extra-cmake-modules
- pacman-contrib
- kdesu5
- ksshaskpass
- bash
- pak 1:5.5.3.r11.g3e65d8e-1 (`git clone -b 3e65d8e8a15a12e2f0fe1a7ed2d09dd944d65ff1 https://gitlab.com/nycko123/pak.git`)
- qt5-base
- qt5-charts
- kwidgetsaddons5
- kcoreaddons5
- kcrash5
- kdbusaddons5
- kdoctools5
- ki18n5
- kxmlgui5
- knotifications5


### Optional dependencies

- devtools (pkgtcl)
- git (POLAUR sync)
- auracle-git (AUR)
- reflector (mirrorlists)
- gcovr (tests)


### Configuration

It's required to set TERM environment variable globally.
For example within <b>.bashrc</b> file in home directory.
For example such line can be added - <b>TERM=konsole</b> (or other terminal app you are using)

### Installation

```
git clone https://github.com/juliagoda/pak-gui.git
cd pak-gui
mkdir build
cd build
cmake -DRUN_TESTS=OFF ..
make -j 2
sudo make install
```

<br/>

## Installation from PKGBUILD  

```
git clone https://github.com/archlinux-lucjan/archlinux-packages.git  
cd archlinux-packages/pak-gui-git
makepkg -srci
```

<br/>

## Running tests with sources


It's important to run tests before running code coverage:

```
cmake -DRUN_TESTS=ON ..
make -j 2
bin/pak-qtests
gcovr -r . -j 2 -f ../src/src/.*cpp
```

<br/>

## Package remove

### Sources  

```
sudo make uninstall
```

### PKGBUILD   

```
sudo pacman -Rs pak-gui-git
```

<br/>

## Attention

1) pak -C (the command that fills the middle column can run slowly, especially when POLAUR repositories are synchronized)
2) Do not use the application in test mode if you are not a programmer.
3) The password window application named ksshaskpass has a bug that does not allow you to save the specified password for future use. A workaround or other solution will be applied.
