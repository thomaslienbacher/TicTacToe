//
// Created by Thomas Lienbacher on 16.09.2018.
//

#include <iostream>
#include "gamescene.hpp"
#include "window.hpp"

GameScene::GameScene(GameInfo *gameInfo) : gameInfo(gameInfo) {
    loadAnimTex.loadFromFile("res/load_circle.png");
    loadAnimTex.setSmooth(true);

    ipInput.setFont(gameInfo->font);
    ipInput.setSize({Window::VWIDTH / 2 - 200, Window::VHEIGHT / 2, 400, 60});
    ipInput.setMaxchars(21);

    loadAnim.setPosition(Window::VWIDTH / 2, Window::VHEIGHT / 2);
    loadAnim.setTexture(loadAnimTex, true);
    const sf::IntRect &ir = loadAnim.getTextureRect();
    loadAnim.setOrigin(ir.width / 2, ir.height / 2);


    layoutTex.loadFromFile("res/layout.png");
    layout.setTexture(layoutTex, false);
    auto sr = layoutTex.getSize();
    layout.setOrigin(sr.x / 2, sr.y / 2);
    layout.setPosition(Window::VWIDTH / 2, Window::VHEIGHT / 2 + 30);

    net.state = Network::IDLE;
}

void GameScene::update(float delta) {
    if(net.state == Network::IDLE) {
        if(gameInfo->networkType == HOST) net.state = Network::SETUP;
        if(gameInfo->networkType == CLIENT) net.state = Network::GATHERING_INFO;
    }

    if(net.state == Network::GATHERING_INFO) {
        ipInput.update(delta);

        if(ipInput.isEntered()) {
            net.state = Network::SETUP;
            net.ip = ipInput.getInput();
        }
    }

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
        loadAnim.rotate(200.0f * delta);
    }

    if (net.state == Network::CONNECTED) {

    }
}

void GameScene::draw(std::shared_ptr<sf::RenderWindow> &window) {
    if(net.state == Network::GATHERING_INFO) {
        static sf::Text ipText("Enter IP Address", gameInfo->font);

        ipText.setPosition(Window::VWIDTH / 2, Window::VHEIGHT / 2 - 50);
        auto ir = ipText.getLocalBounds();
        ipText.setOrigin(ir.width / 2, ir.height / 2);
        ipText.setFillColor(sf::Color::Black);

        window->draw(ipText);

        ipInput.draw(window);
    }

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

        title.setPosition(Window::VWIDTH / 2, 20);
        auto ir = title.getLocalBounds();
        title.setOrigin(ir.width / 2, ir.height / 2);
        title.setFillColor(sf::Color::Black);

        window->draw(title);
        window->draw(layout);
    }
}

void GameScene::handle(sf::Event event) {
    if(net.state == Network::GATHERING_INFO) {
        ipInput.handle(event);
    }
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
        if (net->socket.connect(net->ip, PORT) == sf::Socket::Done) {
            net->state = GameScene::Network::CONNECTED;
        } else {
            std::cout << "didnt connect" << std::endl;
        }

        sf::sleep(sf::milliseconds(200));
    }
}