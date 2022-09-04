# Tic Tac Toe

A multiplayer Tic Tac Toe game which can be played in a local network.

Compile using CMake or by opening the Project in CLion.

Dependencies:
* C++ 17
* SFML 2.5

## Building on Linux (Fedora)
* Install dependencies: `doas dnf install SFML SFML-devel`
* Generate Makefile: `cmake -S . -B cmake-build-debug -DCMAKE_BUILD_TYPE=Debug`
* Move to the dir and `make`

