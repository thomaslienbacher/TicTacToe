//
// Created by Thomas Lienbacher on 16.09.2018.
//

#include <iostream>
#include "gamescene.hpp"

GameScene::GameScene(GameInfo *gameInfo) : gameInfo(gameInfo) {}

void GameScene::update(float delta) {

    if (!net.networkSetup) {
        if (gameInfo->networkType == HOST) {
            pthread_create(&net.thread, NULL, hostControll, this);
        }

        if (gameInfo->networkType == CLIENT) {
            pthread_create(&net.thread, NULL, clientControll, this);
        }

        net.networkSetup = true;
    }
}

void GameScene::draw(std::shared_ptr<sf::RenderWindow> &window) {

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
    } else {
        std::cout << "looking" << std::endl;
    }
}

void *clientControll(void *gameScene) {
    GameScene::Network *net = ((GameScene*) gameScene)->getNet();

    if (net->socket.connect("127.0.0.1", PORT) == sf::Socket::Done) {
        std::cout << "connected" << std::endl;
    } else {
        std::cout << "not connected" << std::endl;
    }
}