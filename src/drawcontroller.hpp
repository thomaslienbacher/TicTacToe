//
// Created by Thomas Lienbacher on 13.09.2018.
//

#ifndef TICTACTOE_DRAWCONTROLLER_HPP
#define TICTACTOE_DRAWCONTROLLER_HPP


#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "gameinfo.hpp"

class DrawController {
    GameInfo* gameInfo;

public:
    DrawController(GameInfo *gameInfo);

    void draw(float delta, const std::shared_ptr<sf::RenderWindow> &window);

};


#endif //TICTACTOE_DRAWCONTROLLER_HPP
