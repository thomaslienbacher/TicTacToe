//
// Created by Thomas Lienbacher on 13.09.2018.
//

#ifndef TICTACTOE_GAMEINFO_HPP
#define TICTACTOE_GAMEINFO_HPP


#include "sfml.hpp"
#include "map.hpp"
#include "button.hpp"

struct GameInfo {
    sf::Texture crossTex;
    sf::Texture circleTex;
    sf::Texture layoutTex;
    sf::Texture buttonTex;

    Map map;
    Button playHostButton;
    Button playClientButton;

    GameInfo();
    ~GameInfo() = default;
};


#endif //TICTACTOE_GAMEINFO_HPP
