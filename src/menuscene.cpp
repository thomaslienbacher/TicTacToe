//
// Created by Thomas Lienbacher on 16.09.2018.
//

#include <iostream>
#include "menuscene.hpp"

MenuScene::MenuScene() {
    buttonTex.loadFromFile("res/button.png");
    font.loadFromFile("res/roboto.ttf");

    playHostButton.setText("Play as Host");
    playHostButton.setTexture(buttonTex);
    playHostButton.setPosition({100, 300});
    playHostButton.setFont(font);
    playHostButton.setOnclick([]{std::cout << "play as host clicked" << std::endl;});

    playClientButton.setText("Play as Client");
    playClientButton.setTexture(buttonTex);
    playClientButton.setPosition({100, 100});
    playClientButton.setFont(font);
    playClientButton.setOnclick([]{std::cout << "play as client clicked" << std::endl;});
}

void MenuScene::update(float delta) {

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
