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
#define RESET_TIME 5.0f

//TODO: cleanup this class
class GameScene : public EventHandler {

    //TODO: seperate gamescene from networking stuff and create a scene for that

    GameInfo *gameInfo;
    sf::Texture crossTex;
    sf::Texture circleTex;
    sf::Texture layoutTex;
    sf::Sprite layout;

    Map map;
    Button mapButtons[3][3];
    char player;
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
};


#endif //TICTACTOE_GAMESCENE_HPP
