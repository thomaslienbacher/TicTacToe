//
// Created by Thomas Lienbacher on 23.09.2018.
//

#ifndef TICTACTOE_NETWORKSCENE_HPP
#define TICTACTOE_NETWORKSCENE_HPP

#include <SFML/Network.hpp>
#include "eventhandler.hpp"
#include "gameinfo.hpp"
#include "textinput.hpp"
#include <thread>

class NetworkScene : public EventHandler {
    struct ThreadInfo {
        static constexpr unsigned short PORT = 45302;

        sf::TcpListener listener;
        sf::TcpSocket socket;
        std::string ip;

        enum {
            IDLE, GATHERING_INFO, SETUP, LOADING, CONNECTED
        } state;
    };

    GameInfo *gameInfo;
    sf::Texture loadAnimTex;
    TextInput ipInput;
    sf::Sprite loadAnim;
    sf::Text loadText;
    sf::Text ipText;

    std::thread thread;
    ThreadInfo threadInfo;

public:
    explicit NetworkScene(GameInfo *gameInfo);

    void update(float delta);

    void draw(sf::RenderWindow &window);

    void handle(sf::Event &event) override;
};


#endif //TICTACTOE_NETWORKSCENE_HPP
