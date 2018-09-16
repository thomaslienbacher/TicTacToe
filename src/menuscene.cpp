//
// Created by Thomas Lienbacher on 16.09.2018.
//

#include <iostream>
#include "menuscene.hpp"

MenuScene::MenuScene(GameInfo *gameInfo) : gameInfo(gameInfo) {
    buttonTex.loadFromFile("res/button.png");

    playHostButton.setText("Play as Host");
    playHostButton.setTexture(buttonTex);
    playHostButton.setBounds({100, 300, 100, 100});
    playHostButton.setOnclick([]{std::cout << "play as host clicked" << std::endl;});

    playClientButton.setText("Play as Client");
    playClientButton.setTexture(buttonTex);
    playClientButton.setBounds({100, 150, 100, 100});
    playClientButton.setOnclick([]{std::cout << "play as host clicked" << std::endl;});
}

void MenuScene::update(float delta) {

    //buttons
    auto pos = sf::Mouse::getPosition(*gameInfo->window->getWindow().get());

    playHostButton.check(pos);
    playClientButton.check(pos);
}

void MenuScene::draw(std::shared_ptr<sf::RenderWindow> &window) {
    playHostButton.draw(window);
    playClientButton.draw(window);
}
