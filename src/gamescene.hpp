//
// Created by Thomas Lienbacher on 16.09.2018.
//

#ifndef TICTACTOE_GAMESCENE_HPP
#define TICTACTOE_GAMESCENE_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include "map.hpp"
#include "eventhandler.hpp"
#include "gameinfo.hpp"
#include "animation.hpp"
#include "textinput.hpp"
#include "button.hpp"
#include <memory>
#include <pthread.h>

//TODO: correctly asign either defines or constexpr type constants
#define PORT 45302
#define RESET_TIME 5.0f

//TODO: cleanup this class
class GameScene : public EventHandler {
public:

    //TODO: seperate gamescene from networking stuff and create a scene for that
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
    //TODO: implement internal gamestate system as opposed the "figure out where we are and do things"

public:
    explicit GameScene(GameInfo *gameInfo);
    //TODO: create a proper destructor then close sockets, kill threads, free resources

    void update(float delta);
    void draw(std::shared_ptr<sf::RenderWindow>& window);

    void handle(sf::Event event) override;

    Network* getNet();
};

void *hostControll(void *gameScene);
void *clientControll(void *gameScene);


#endif //TICTACTOE_GAMESCENE_HPP
