//
// Created by Thomas Lienbacher on 16.09.2018.
//

#ifndef TICTACTOE_GAMEINFO_HPP
#define TICTACTOE_GAMEINFO_HPP


#include "window.hpp"

enum State {MENU, GAME};

struct GameInfo {
    Window *window;
    State *gamestate;
};


#endif //TICTACTOE_GAMEINFO_HPP
