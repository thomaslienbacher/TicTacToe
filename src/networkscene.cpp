//
// Created by Thomas Lienbacher on 23.09.2018.
//

#include "networkscene.hpp"
#include "window.hpp"
#include "map.hpp"
#include <iostream>
#include <cmath>

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

    ipText.setString("Enter IP Address");
    ipText.setFont(gameInfo->font);
    ipText.setPosition(std::lroundf(Window::VWIDTH / 2), std::lroundf(Window::VHEIGHT / 2 - 50));
    auto fr = ipText.getLocalBounds();
    ipText.setOrigin(std::lroundf(fr.width / 2), std::lroundf(fr.height / 2));
    ipText.setFillColor(sf::Color::Black);

    loadText.setString("Waiting for connection...");
    loadText.setFont(gameInfo->font);
    loadText.setPosition(std::lroundf(Window::VWIDTH / 2), std::lroundf(Window::VHEIGHT / 2 + 100));
    fr = loadText.getLocalBounds();
    loadText.setOrigin(std::lroundf(fr.width / 2), std::lroundf(fr.height / 2));
    loadText.setFillColor(sf::Color::Black);

    threadInfo.state = ThreadInfo::IDLE;
}

void NetworkScene::update(float delta) {
    if (threadInfo.state == ThreadInfo::IDLE) {
        if (gameInfo->networkType == HOST) threadInfo.state = ThreadInfo::SETUP;
        if (gameInfo->networkType == CLIENT) threadInfo.state = ThreadInfo::GATHERING_INFO;
    }

    if (threadInfo.state == ThreadInfo::GATHERING_INFO) {
        ipInput.update(delta);

        if (ipInput.isEntered()) {
            threadInfo.state = ThreadInfo::SETUP;
            threadInfo.ip = ipInput.getInput();
        }
    }

    if (threadInfo.state == ThreadInfo::SETUP) {
        if (gameInfo->networkType == HOST) {
            //host thread
            thread = std::thread([=] {
                auto ti = &threadInfo;
                ti->listener.listen(ThreadInfo::PORT);

                if (ti->listener.accept(ti->socket) == sf::Socket::Done) {
                    ti->state = ThreadInfo::CONNECTED;
                    ti->socket.setBlocking(false);
                    ti->listener.close();
                } else {
                    std::cerr << "Couldn't accept the client!" << std::endl;
                }
            });
            thread.detach();
            gameInfo->me = Map::C_CROSS;
        }

        if (gameInfo->networkType == CLIENT) {
            //client thread
            thread = std::thread([=] {
                auto ti = &threadInfo;

                while (ti->state != ThreadInfo::CONNECTED) {
                    if (ti->socket.connect(ti->ip, ThreadInfo::PORT) == sf::Socket::Done) {
                        ti->state = ThreadInfo::CONNECTED;
                        ti->socket.setBlocking(false);

                    } else {
                        std::cerr << "Couldn't connect to a host!" << std::endl;
                    }

                    sf::sleep(sf::milliseconds(100));
                }
            });
            thread.detach();
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
        auto fr = ipText.getLocalBounds();
        ipText.setOrigin(std::lroundf(fr.width / 2), std::lroundf(fr.height / 2));

        window->draw(ipText);
        ipInput.draw(window);
    }

    if (threadInfo.state == ThreadInfo::LOADING) {
        auto fr = loadText.getLocalBounds();
        loadText.setOrigin(std::lroundf(fr.width / 2), std::lroundf(fr.height / 2));

        window->draw(loadAnim);
        window->draw(loadText);
    }
}

void NetworkScene::handle(sf::Event event) {
    if (threadInfo.state == ThreadInfo::GATHERING_INFO) {
        ipInput.handle(event);
    }
}
