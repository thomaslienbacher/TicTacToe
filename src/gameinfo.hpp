//
// Created by Thomas Lienbacher on 17.09.2018.
//

#ifndef TICTACTOE_GAMEINFO_HPP
#define TICTACTOE_GAMEINFO_HPP

#include <SFML/Network.hpp>

enum State {MENU, NETWORK, GAME};
enum NetworkType {HOST, CLIENT};

struct GameInfo {
    State gamestate;
    NetworkType networkType;
    sf::TcpSocket *socket;
    sf::Font font;
    char me;
};


#endif //TICTACTOE_GAMEINFO_HPP
