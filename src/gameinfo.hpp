//
// Created by Thomas Lienbacher on 17.09.2018.
//

#ifndef TICTACTOE_GAMEINFO_HPP
#define TICTACTOE_GAMEINFO_HPP


enum State {MENU, GAME};
enum NetworkType {HOST, CLIENT};

struct GameInfo {
    State gamestate;
    NetworkType networkType;
};


#endif //TICTACTOE_GAMEINFO_HPP
