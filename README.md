# pak-gui

pak-gui is a pacman wrapper, AUR and POLAUR helper of [Damian N](https://gitlab.com/nycko123/pak) enhanced with GUI.

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
cmake -DRUN_TESTS=OFF ..
make -j 2
```

### Running tests

```
cmake -DRUN_TESTS=ON ..
make -j 2
make test
gcovr -r .
```

### Attention

1) pak -C (the command that fills the middle column can run slowly, especially when POLAUR repositories are synchronized)
2) Do not use the application in test mode if you are not a programmer.
3) The password window application named ksshaskpass has a bug that does not allow you to save the specified password for future use. A workaround or other solution will be applied.

### TODO

- [ ] Documentation for users
- [ ] Documentation for developers
- [ ] Icons for app
- [ ] Translations to other languages than English or Polish
- [ ] Finding workaround for ksshaskpass' bug
- [ ] Stack of actions (undo operation)
- [ ] Mirrorlists application in GUI
- [ ] Keys application in GUI (signing)
- [ ] Port to KF6/Qt6 after official and stable release of KF6
- [ ] Warnings reduction
- [ ] Updates column run when requested (optimization)
- [ ] Building fix when tbb is installed
- [ ] Align the contents of tooltip
- [ ] Milestone creation with tasks for next version
