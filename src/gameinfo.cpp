//
// Created by Thomas Lienbacher on 13.09.2018.
//

#include "gameinfo.hpp"

GameInfo::GameInfo()
: playHostButton("Play as Host", buttonTex, {0, 0, 100, 100}, ||() {}), playClientButton("") {
    crossTex.loadFromFile("res/cross.png");
    circleTex.loadFromFile("res/circle.png");
    layoutTex.loadFromFile("res/layout.png");
    buttonTex.loadFromFile("res/button.png");
}