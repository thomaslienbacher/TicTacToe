//
// Created by Thomas Lienbacher on 16.09.2018.
//

#include <iostream>
#include <sstream>
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

    crossTex.loadFromFile("res/cross.png");
    crossTex.setSmooth(true);

    circleTex.loadFromFile("res/circle.png");
    circleTex.setSmooth(true);

    net.state = Network::IDLE;
    player = Map::C_CROSS;
    moveMade = false;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            auto sr = crossTex.getSize();

            mapButtons[i][j].setTexture(crossTex);
            mapButtons[i][j].setPosition({(float)i * (layoutTex.getSize().x / 3.0f + 3.0f) + layout.getPosition().x - layout.getOrigin().x + sr.x / 2,
                                          (float)j * (layoutTex.getSize().y / 3.0f + 3.0f) + layout.getPosition().y - layout.getOrigin().y + sr.y / 2});
            mapButtons[i][j].setOnclick([i, j, this] {
                if (this->player == this->me && !map.getAt(i, j)) {
                    moveMade = true;
                    toPlace = {i, j};
                }
            });
        }
    }
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
            me = Map::C_CROSS;
        }

        if (gameInfo->networkType == CLIENT) {
            pthread_create(&net.thread, NULL, clientControll, this);
            me = Map::C_CIRCLE;
        }

        net.state = Network::LOADING;
    }

    if (net.state == Network::LOADING) {
        loadAnim.rotate(200.0f * delta);
    }

    if (net.state == Network::CONNECTED) {
        if(moveMade) {
            sf::Packet sndPacket;
            sndPacket << toPlace.x;
            sndPacket << toPlace.y;
            sndPacket.endOfPacket();
            net.socket.send(sndPacket);
            map.setAt(toPlace.x, toPlace.y, player);

            if(player == Map::C_CROSS) player = Map::C_CIRCLE;
            else if(player == Map::C_CIRCLE) player = Map::C_CROSS;

            moveMade = false;
        }

        sf::Packet rcvPacket;
        if (net.socket.receive(rcvPacket) == sf::Socket::Status::Done) {
            int x, y;
            rcvPacket >> x;
            rcvPacket >> y;

            map.setAt(x, y, player);
            if(player == Map::C_CROSS) player = Map::C_CIRCLE;
            else if(player == Map::C_CIRCLE) player = Map::C_CROSS;
        }
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
        std::stringstream st;
        char winner = map.getWinner();

        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                std::cout << map.getAt(i, j) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;

        if(!winner) {
            st << "You: ";
            st << me;
            st << " ";
            st << (int) winner;
        } else {
            if(me == winner) st << "You won!";
            else st << "You lost!";
        }

        static sf::Text title(st.str(), gameInfo->font, 25);

        title.setPosition(Window::VWIDTH / 2, 20);
        auto ir = title.getLocalBounds();
        title.setOrigin(ir.width / 2, ir.height / 2);
        title.setFillColor(sf::Color::Black);

        window->draw(title);
        window->draw(layout);

        static sf::Sprite s;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                char c = map.getAt(i, j);

                if(c == Map::C_CROSS) s.setTexture(crossTex, true);
                else if(c == Map::C_CIRCLE) s.setTexture(circleTex, true);
                else continue;

                s.setScale(0.9f, 0.9f);
                auto sr = s.getTexture()->getSize();
                s.setOrigin(sr.x / 2, sr.y / 2);
                s.setPosition((float)i * (layoutTex.getSize().x / 3.0f + 3.0f) + layout.getPosition().x - layout.getOrigin().x + sr.x / 2,
                              (float)j * (layoutTex.getSize().y / 3.0f + 3.0f) + layout.getPosition().y - layout.getOrigin().y + sr.y / 2);
                window->draw(s);
            }
        }
    }
}

void GameScene::handle(sf::Event event) {
    if(net.state == Network::GATHERING_INFO) {
        ipInput.handle(event);
    }

    if(net.state == Network::CONNECTED) {
        if(event.type == sf::Event::MouseButtonPressed) {
            if(event.mouseButton.button == sf::Mouse::Button::Left){
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        mapButtons[i][j].mouseDown(event.mouseButton.x, event.mouseButton.y);
                    }
                }
            }
        }

        if(event.type == sf::Event::MouseButtonReleased) {
            if(event.mouseButton.button == sf::Mouse::Button::Left){
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        mapButtons[i][j].mouseUp(event.mouseButton.x, event.mouseButton.y);
                    }
                }
            }
        }
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
        net->socket.setBlocking(false);
    } else {
        std::cout << "didnt accept" << std::endl;
    }
}

void *clientControll(void *gameScene) {
    GameScene::Network *net = ((GameScene *) gameScene)->getNet();

    while (net->state != GameScene::Network::CONNECTED) {
        if (net->socket.connect(net->ip, PORT) == sf::Socket::Done) {
            net->state = GameScene::Network::CONNECTED;
            net->socket.setBlocking(false);

        } else {
            std::cout << "didnt connect" << std::endl;
        }

        sf::sleep(sf::milliseconds(200));
    }
}