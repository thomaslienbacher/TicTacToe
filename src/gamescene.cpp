//
// Created by Thomas Lienbacher on 16.09.2018.
//

#include <iostream>
#include "gamescene.hpp"
#include "window.hpp"

GameScene::GameScene(GameInfo *gameInfo) : gameInfo(gameInfo) {
    loadAnimTex.loadFromFile("res/explosion.png");

    loadingAnimation.setFps(10.5f);
    loadingAnimation.setTexture(loadAnimTex, 2, 4);
    loadingAnimation.setPosition({Window::VWIDTH / 3, Window::VHEIGHT / 3});
}

void GameScene::update(float delta) {
    if (net.state == Network::SETUP) {
        if (gameInfo->networkType == HOST) {
            pthread_create(&net.thread, NULL, hostControll, this);
        }

        if (gameInfo->networkType == CLIENT) {
            pthread_create(&net.thread, NULL, clientControll, this);
        }

        net.state = Network::LOADING;
    }

    if(net.state == Network::LOADING) {
        loadingAnimation.update(delta);
    }
}

void GameScene::draw(std::shared_ptr<sf::RenderWindow> &window) {
    if(net.state == Network::LOADING) {
        loadingAnimation.draw(window);
    }
}

void GameScene::handle(sf::Event event) {

}

GameScene::Network* GameScene::getNet() {
    return &net;
}

void *hostControll(void *gameScene) {
    GameScene::Network *net = ((GameScene*) gameScene)->getNet();
    net->listener.listen(PORT);

    if (net->listener.accept(net->socket) == sf::Socket::Done) {
        std::cout << "found one" << std::endl;
        net->state = GameScene::Network::CONNECTED;
    } else {
        std::cout << "looking" << std::endl;
    }
}

void *clientControll(void *gameScene) {
    GameScene::Network *net = ((GameScene*) gameScene)->getNet();

    if (net->socket.connect("127.0.0.1", PORT) == sf::Socket::Done) {
        std::cout << "connected" << std::endl;
        net->state = GameScene::Network::CONNECTED;
    } else {
        std::cout << "not connected" << std::endl;
    }
}