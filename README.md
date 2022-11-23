# pak-gui

pak-gui is a pacman wrapper, AUR and POLAUR helper of [Damian N](https://gitlab.com/nycko123/pak) enhanced with GUI.

![Browse](https://github.com/juliagoda/pak-gui/blob/main/pak-gui.png)

[![pak-gui](https://github.com/juliagoda/pak-gui/actions/workflows/ci.yml/badge.svg?branch=main)](https://github.com/juliagoda/pak-gui/actions/workflows/ci.yml)
![CodeFactor Grade](https://img.shields.io/codefactor/grade/github/juliagoda/pak-gui)


<br/>

## Installing from source

### Dependencies - Qt5

- cmake
- pak (`git clone -b e4ee7efea11d48f3a2af32771bd8494bed2 https://gitlab.com/nycko123/pak.git`)
- qt5-base
- qt5-charts
- gcovr (optional for tests)
- gtest (optional for tests)


### Dependencies - Qt6

- cmake
- pak (`git clone -b e4ee7efea11d48f3a2af32771bd8494bed2 https://gitlab.com/nycko123/pak.git`)
- qt6-base
- qt6-charts
- gcovr (optional for tests)
- gtest (optional for tests)

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
