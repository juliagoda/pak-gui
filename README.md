# pak-gui

pak-gui is a pacman wrapper, AUR and POLAUR helper of [Damian N](https://gitlab.com/nycko123/pak) enhanced with GUI.

![Browse](https://raw.githubusercontent.com/CachyOS/pak-gui/main/resources/icons/app/64-apps-pak-gui.png)

[![pak-gui](https://github.com/CachyOS/pak-gui/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/CachyOS/pak-gui/actions/workflows/ci.yml)
![CodeFactor Grade](https://img.shields.io/codefactor/grade/github/CachyOS/pak-gui/main)


<br/>

## Installing from source

### Required dependencies - Qt5

- cmake
- extra-cmake-modules
- pacman-contrib
- kdesu
- ksshaskpass
- bash
- pak 1:5.5.3.r11.g3e65d8e-1 (`git clone -b 3e65d8e8a15a12e2f0fe1a7ed2d09dd944d65ff1 https://gitlab.com/nycko123/pak.git`)
- qt5-base
- qt5-charts
- kwidgetsaddons
- kcoreaddons
- kcrash
- kdbusaddons
- kdoctools
- ki18n
- kxmlgui
- knotifications


### Optional dependencies

- devtools (pkgtcl)
- git (POLAUR sync)
- auracle-git (AUR)
- reflector (mirrorlists)
- gcovr (tests)

<br/>

### Configuration

It's required to set TERM environment variable globally.
For example within <b>.bashrc</b> file in home directory.
For example such line can be added - <b>TERM=konsole</b> (or other terminal app you are using)

### Installation

```
mkdir build
cd build
cmake ..
make
```

### Running tests

```
cmake -DRUN_TESTS=ON ..
make
make test
gcovr -r .
```
