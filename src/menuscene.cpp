//
// Created by Thomas Lienbacher on 16.09.2018.
//

#include <iostream>
#include "menuscene.hpp"
#include "window.hpp"

MenuScene::MenuScene(GameInfo *gameInfo) : gameInfo(gameInfo) {
    buttonTex.loadFromFile("res/button.png");
    font.loadFromFile("res/roboto.ttf");

    playHostButton.setText("Play as Host");
    playHostButton.setTexture(buttonTex);
    playHostButton.setPosition({Window::VWIDTH / 2 - buttonTex.getSize().x / 2,
                                Window::VHEIGHT / 4 - buttonTex.getSize().y / 2});
    playHostButton.setFont(font);
    playHostButton.setOnclick([gameInfo]{
        gameInfo->gamestate = GAME;
        gameInfo->networkType = HOST;
    });

    playClientButton.setText("Play as Client");
    playClientButton.setTexture(buttonTex);
    playClientButton.setPosition({Window::VWIDTH / 2 - buttonTex.getSize().x / 2,
                                  Window::VHEIGHT / 4.0f*3.0f - buttonTex.getSize().y / 2});
    playClientButton.setFont(font);
    playClientButton.setOnclick([gameInfo]{
        gameInfo->gamestate = GAME;
        gameInfo->networkType = CLIENT;
    });
}

void MenuScene::draw(std::shared_ptr<sf::RenderWindow> &window) {
    playHostButton.draw(window);
    playClientButton.draw(window);
}

void MenuScene::handle(sf::Event event) {
    if(event.type == sf::Event::MouseButtonPressed) {
        if(event.mouseButton.button == sf::Mouse::Button::Left){
            playHostButton.mouseDown(event.mouseButton.x, event.mouseButton.y);
            playClientButton.mouseDown(event.mouseButton.x, event.mouseButton.y);
        }
    }

    if(event.type == sf::Event::MouseButtonReleased) {
        if(event.mouseButton.button == sf::Mouse::Button::Left){
            playHostButton.mouseUp(event.mouseButton.x, event.mouseButton.y);
            playClientButton.mouseUp(event.mouseButton.x, event.mouseButton.y);
        }
    }
}
