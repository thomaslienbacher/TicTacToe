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
#include "button.hpp"
#include <memory>
#include <pthread.h>

#define PORT 45302
#define RESET_TIME 5.0f

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
    sf::Sprite layout;
    sf::Texture loadAnimTex;

    TextInput ipInput;
    sf::Sprite loadAnim;

    Network net;
    Map map;
    Button mapButtons[3][3];
    char player;
    char me;
    sf::Vector2i toPlace;
    bool moveMade;
    bool gameOver = false;
    float time = 0;

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
