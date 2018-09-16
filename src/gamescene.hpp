//
// Created by Thomas Lienbacher on 16.09.2018.
//

#ifndef TICTACTOE_GAMESCENE_HPP
#define TICTACTOE_GAMESCENE_HPP

#include "sfml.hpp"
#include "map.hpp"
#include "gameinfo.hpp"

class GameScene {

    GameInfo *gameInfo;
    sf::Texture crossTex;
    sf::Texture circleTex;
    sf::Texture layoutTex;
    Map map;

public:
    GameScene(GameInfo *gameInfo);

    void update(float delta);
    void draw(std::shared_ptr<sf::RenderWindow>& window);
};


#endif //TICTACTOE_GAMESCENE_HPP
