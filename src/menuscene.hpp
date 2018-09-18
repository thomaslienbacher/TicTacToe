//
// Created by Thomas Lienbacher on 16.09.2018.
//

#ifndef TICTACTOE_MENUSCENE_HPP
#define TICTACTOE_MENUSCENE_HPP

#include "sfml.hpp"
#include "button.hpp"
#include "eventhandler.hpp"
#include "gameinfo.hpp"
#include <memory>

class MenuScene : public EventHandler {

    GameInfo *gameInfo;
    sf::Texture buttonTex;
    sf::Font font;
    Button playHostButton;
    Button playClientButton;

public:
    explicit MenuScene(GameInfo *gameInfo);

    void draw(std::shared_ptr<sf::RenderWindow> &window);
    void handle(sf::Event event) override;
};


#endif //TICTACTOE_MENUSCENE_HPP
