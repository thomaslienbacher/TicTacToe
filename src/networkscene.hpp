//
// Created by Thomas Lienbacher on 23.09.2018.
//

#ifndef TICTACTOE_NETWORKSCENE_HPP
#define TICTACTOE_NETWORKSCENE_HPP


#include <pthread.h>
#include <SFML/Network.hpp>
#include "eventhandler.hpp"
#include "gameinfo.hpp"
#include "textinput.hpp"

class NetworkScene : public EventHandler {
public:

    struct ThreadInfo {
        sf::TcpListener listener;
        sf::TcpSocket socket;
        std::string ip;
        const unsigned short port = 45302;

        enum {
            IDLE, GATHERING_INFO, SETUP, LOADING, CONNECTED
        } state;
    };

private:

    GameInfo *gameInfo;
    sf::Texture loadAnimTex;
    TextInput ipInput;
    sf::Sprite loadAnim;
    sf::Text loadText;
    sf::Text ipText;

    pthread_t thread;
    ThreadInfo threadInfo;

public:
    explicit NetworkScene(GameInfo *gameInfo);

    void update(float delta);
    void draw(std::shared_ptr<sf::RenderWindow>& window);
    void handle(sf::Event event) override;
};

void *hostThread(void *threadInfo);
void *clientThread(void *threadInfo);


#endif //TICTACTOE_NETWORKSCENE_HPP
