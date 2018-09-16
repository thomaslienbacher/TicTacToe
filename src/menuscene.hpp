//
// Created by Thomas Lienbacher on 16.09.2018.
//

#ifndef TICTACTOE_MENUSCENE_HPP
#define TICTACTOE_MENUSCENE_HPP

#include "sfml.hpp"
#include "button.hpp"

class MenuScene {

    GameInfo* gameInfo;
    sf::Texture buttonTex;
    Button playHostButton;
    Button playClientButton;

public:
    MenuScene(GameInfo *gameInfo);

    void update(float delta);
    void draw(std::shared_ptr<sf::RenderWindow>& window);
};


#endif //TICTACTOE_MENUSCENE_HPP
