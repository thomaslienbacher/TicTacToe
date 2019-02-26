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

class GameScene : public EventHandler {
    static constexpr float RESET_TIME = 5.0f;

    GameInfo *gameInfo;
    sf::Texture crossTex;
    sf::Texture circleTex;
    sf::Texture layoutTex;
    sf::Sprite layout;
    sf::Text title;

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

    void update(float delta);

    void draw(sf::RenderWindow &window);

    void handle(sf::Event &event) override;
};


#endif //TICTACTOE_GAMESCENE_HPP
