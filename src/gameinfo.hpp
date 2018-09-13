//
// Created by Thomas Lienbacher on 13.09.2018.
//

#ifndef TICTACTOE_GAMEINFO_HPP
#define TICTACTOE_GAMEINFO_HPP


#include "sfml.hpp"

class GameInfo {
    sf::Texture crossTex;
    sf::Texture circleTex;

    char map[3][3];

public:
    void loadResources();

};


#endif //TICTACTOE_GAMEINFO_HPP
