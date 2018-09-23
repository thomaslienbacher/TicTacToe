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

#define PORT 45302

class NetworkScene : public EventHandler {
public:

    struct ThreadInfo {
        sf::TcpListener listener;
        sf::TcpSocket socket;
        std::string ip;

        enum {
            IDLE, GATHERING_INFO, SETUP, LOADING, CONNECTED
        } state;
    };

private:

    GameInfo *gameInfo;
    sf::Texture loadAnimTex;
    TextInput ipInput;
    sf::Sprite loadAnim;

    pthread_t thread;
    ThreadInfo threadInfo;

public:
    explicit NetworkScene(GameInfo *gameInfo);

    void update(float delta);
    void draw(std::shared_ptr<sf::RenderWindow>& window);
    void handle(sf::Event event) override;

};

void *hostControll(void *threadInfo);
void *clientControll(void *threadInfo);


#endif //TICTACTOE_NETWORKSCENE_HPP
