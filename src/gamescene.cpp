//
// Created by Thomas Lienbacher on 16.09.2018.
//

#include <iostream>
#include "gamescene.hpp"
#include "window.hpp"

GameScene::GameScene(GameInfo *gameInfo) : gameInfo(gameInfo) {
    loadAnimTex.loadFromFile("res/load_circle.png");
    loadAnimTex.setSmooth(true);

    loadAnim.setPosition(Window::VWIDTH / 2, Window::VHEIGHT / 2);
    loadAnim.setTexture(loadAnimTex, true);
    const sf::IntRect &ir = loadAnim.getTextureRect();
    loadAnim.setOrigin(ir.width / 2, ir.height / 2);
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

    if (net.state == Network::LOADING) {
        loadAnim.rotate(210.0f * delta);
    }
}

void GameScene::draw(std::shared_ptr<sf::RenderWindow> &window) {
    if (net.state == Network::LOADING) {
        window->draw(loadAnim);

        static sf::Text loadText("Waiting for connection...", gameInfo->font);

        loadText.setPosition(Window::VWIDTH / 2, Window::VHEIGHT / 2 + 100);
        auto ir = loadText.getLocalBounds();
        loadText.setOrigin(ir.width / 2, ir.height / 2);
        loadText.setFillColor(sf::Color::Black);

        window->draw(loadText);
    }

    if (net.state == Network::CONNECTED) {
        static sf::Text title("Tic Tac Toe", gameInfo->font, 25);

        title.setPosition(Window::VWIDTH / 2, 40);
        auto ir = title.getLocalBounds();
        title.setOrigin(ir.width / 2, ir.height / 2);
        title.setFillColor(sf::Color::Black);

        window->draw(title);
    }
}

void GameScene::handle(sf::Event event) {

}

GameScene::Network *GameScene::getNet() {
    return &net;
}

void *hostControll(void *gameScene) {
    GameScene::Network *net = ((GameScene *) gameScene)->getNet();
    net->listener.listen(PORT);

    if (net->listener.accept(net->socket) == sf::Socket::Done) {
        net->state = GameScene::Network::CONNECTED;
    } else {
        std::cout << "didnt accept" << std::endl;
    }
}

void *clientControll(void *gameScene) {
    GameScene::Network *net = ((GameScene *) gameScene)->getNet();

    while (net->state != GameScene::Network::CONNECTED) {
        if (net->socket.connect("127.0.0.1", PORT) == sf::Socket::Done) {
            net->state = GameScene::Network::CONNECTED;
        } else {
            std::cout << "didnt connect" << std::endl;
        }

        sf::sleep(sf::milliseconds(200));
    }
}