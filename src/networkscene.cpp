//
// Created by Thomas Lienbacher on 23.09.2018.
//

#include "networkscene.hpp"
#include "window.hpp"
#include "map.hpp"
#include <iostream>

NetworkScene::NetworkScene(GameInfo *gameInfo)
: gameInfo(gameInfo) {
    loadAnimTex.loadFromFile("res/load_circle.png");
    loadAnimTex.setSmooth(true);

    ipInput.setFont(gameInfo->font);
    ipInput.setSize({Window::VWIDTH / 2 - 200, Window::VHEIGHT / 2, 400, 60});

    loadAnim.setPosition(Window::VWIDTH / 2, Window::VHEIGHT / 2);
    loadAnim.setTexture(loadAnimTex, true);
    auto ir = loadAnim.getTextureRect();
    loadAnim.setOrigin(ir.width / 2, ir.height / 2);

    threadInfo.state = ThreadInfo::IDLE;
}

void NetworkScene::update(float delta) {
    if(threadInfo.state == ThreadInfo::IDLE) {
        if(gameInfo->networkType == HOST) threadInfo.state = ThreadInfo::SETUP;
        if(gameInfo->networkType == CLIENT) threadInfo.state = ThreadInfo::GATHERING_INFO;
    }

    if(threadInfo.state == ThreadInfo::GATHERING_INFO) {
        ipInput.update(delta);

        if(ipInput.isEntered()) {
            threadInfo.state = ThreadInfo::SETUP;
            threadInfo.ip = ipInput.getInput();
        }
    }

    //TODO: yield or join threads
    if (threadInfo.state == ThreadInfo::SETUP) {
        if (gameInfo->networkType == HOST) {
            pthread_create(&thread, NULL, hostControll, &this->threadInfo);
            gameInfo->me = Map::C_CROSS;
        }

        if (gameInfo->networkType == CLIENT) {
            pthread_create(&thread, NULL, clientControll, &this->threadInfo);
            gameInfo->me = Map::C_CIRCLE;
        }

        threadInfo.state = ThreadInfo::LOADING;
    }

    if (threadInfo.state == ThreadInfo::LOADING) {
        loadAnim.rotate(200.0f * delta);
    }

    if (threadInfo.state == ThreadInfo::CONNECTED) {
        gameInfo->gamestate = GAME;
        gameInfo->socket = &threadInfo.socket;
    }
}

void NetworkScene::draw(std::shared_ptr<sf::RenderWindow> &window) {
    if (threadInfo.state == ThreadInfo::GATHERING_INFO) {
        static sf::Text ipText("Enter IP Address", gameInfo->font);

        ipText.setPosition(Window::VWIDTH / 2, Window::VHEIGHT / 2 - 50);
        auto ir = ipText.getLocalBounds();
        ipText.setOrigin(ir.width / 2, ir.height / 2);
        ipText.setFillColor(sf::Color::Black);

        window->draw(ipText);

        ipInput.draw(window);
    }

    if (threadInfo.state == ThreadInfo::LOADING) {
        window->draw(loadAnim);

        static sf::Text loadText("Waiting for connection...", gameInfo->font);

        loadText.setPosition(Window::VWIDTH / 2, Window::VHEIGHT / 2 + 100);
        auto ir = loadText.getLocalBounds();
        loadText.setOrigin(ir.width / 2, ir.height / 2);
        loadText.setFillColor(sf::Color::Black);

        window->draw(loadText);
    }
}

void NetworkScene::handle(sf::Event event) {
    if (threadInfo.state == ThreadInfo::GATHERING_INFO) {
        ipInput.handle(event);
    }
}

//TODO: correct error handling
void *hostControll(void *threadInfo) {
    auto ti = (NetworkScene::ThreadInfo*) threadInfo;
    ti->listener.listen(PORT);

    if (ti->listener.accept(ti->socket) == sf::Socket::Done) {
        ti->state = NetworkScene::ThreadInfo::CONNECTED;
        ti->socket.setBlocking(false);
    } else {
        std::cout << "didnt accept" << std::endl;
    }
}

void *clientControll(void *threadInfo) {
    auto ti = (NetworkScene::ThreadInfo*) threadInfo;

    while (ti->state != NetworkScene::ThreadInfo::CONNECTED) {
        if (ti->socket.connect(ti->ip, PORT) == sf::Socket::Done) {
            ti->state = NetworkScene::ThreadInfo::CONNECTED;
            ti->socket.setBlocking(false);

        } else {
            std::cout << "didnt connect" << std::endl;
        }

        sf::sleep(sf::milliseconds(200));
    }
}