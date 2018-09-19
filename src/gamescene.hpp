//
// Created by Thomas Lienbacher on 16.09.2018.
//

#ifndef TICTACTOE_GAMESCENE_HPP
#define TICTACTOE_GAMESCENE_HPP

#include "sfml.hpp"
#include "map.hpp"
#include "eventhandler.hpp"
#include "gameinfo.hpp"
#include "animation.hpp"
#include "textinput.hpp"
#include <memory>
#include <pthread.h>

#define PORT 45302

class GameScene : public EventHandler {
public:

    struct Network {
        pthread_t thread;
        sf::TcpListener listener;
        sf::TcpSocket socket;
        std::string ip;
        enum {IDLE, GATHERING_INFO, SETUP, LOADING, CONNECTED} state;
    };

private:

    GameInfo *gameInfo;
    sf::Texture crossTex;
    sf::Texture circleTex;
    sf::Texture layoutTex;
    sf::Texture loadAnimTex;

    TextInput ipInput;
    sf::Sprite loadAnim;
    Network net;
    Map map;

public:
    explicit GameScene(GameInfo *gameInfo);

    void update(float delta);
    void draw(std::shared_ptr<sf::RenderWindow>& window);

    void handle(sf::Event event) override;

    Network* getNet();
};

void *hostControll(void *gameScene);
void *clientControll(void *gameScene);


#endif //TICTACTOE_GAMESCENE_HPP
