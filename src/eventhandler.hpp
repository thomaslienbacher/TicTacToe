//
// Created by Thomas Lienbacher on 16.09.2018.
//

#ifndef TICTACTOE_EVENTHANDLER_HPP
#define TICTACTOE_EVENTHANDLER_HPP


#include <SFML/Graphics.hpp>

struct EventHandler {
    virtual void handle(sf::Event);
};


#endif //TICTACTOE_EVENTHANDLER_HPP
