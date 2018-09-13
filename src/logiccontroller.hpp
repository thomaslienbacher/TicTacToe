//
// Created by Thomas Lienbacher on 13.09.2018.
//

#ifndef TICTACTOE_LOGICCONTROLLER_HPP
#define TICTACTOE_LOGICCONTROLLER_HPP


#include "gameinfo.hpp"

class LogicController {
    GameInfo* gameInfo;

public:
    LogicController(GameInfo *gameInfo);

    void logic(float delta);
};


#endif //TICTACTOE_LOGICCONTROLLER_HPP
