# pak-gui

pak-gui is a pacman wrapper, AUR and POLAUR helper of [Damian N](https://gitlab.com/nycko123/pak) enhanced with GUI.

![Browse](https://github.com/juliagoda/pak-gui/blob/main/pak-gui.png)

[![pak-gui](https://github.com/juliagoda/pak-gui/actions/workflows/c-cpp.yml/badge.svg?branch=main)](https://github.com/juliagoda/pak-gui/actions/workflows/c-cpp.yml)
![CodeFactor Grade](https://img.shields.io/codefactor/grade/github/juliagoda/pak-gui)


<br/>

## Installing from source

### Dependencies - Qt5

- cmake
- qt5-base
- gcovr (optional for tests)
- gtest (optional for tests)


### Dependencies - Qt6

- cmake
- qt6-base
- gcovr (optional for tests)
- gtest (optional for tests)

<br/>

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
