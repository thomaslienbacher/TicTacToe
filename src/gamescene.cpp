//
// Created by Thomas Lienbacher on 16.09.2018.
//

#include <iomanip>
#include <iostream>
#include <sstream>
#include <cmath>
#include "gamescene.hpp"
#include "window.hpp"
#include "networkscene.hpp"

GameScene::GameScene(GameInfo *gameInfo) : gameInfo(gameInfo) {
    layoutTex.loadFromFile("res/layout.png");
    layout.setTexture(layoutTex, false);
    auto sr = layoutTex.getSize();
    layout.setOrigin(sr.x / 2, sr.y / 2);
    layout.setPosition(Window::VWIDTH / 2, Window::VHEIGHT / 2 + 30);

    crossTex.loadFromFile("res/cross.png");
    crossTex.setSmooth(true);

    circleTex.loadFromFile("res/circle.png");
    circleTex.setSmooth(true);

    title.setFont(gameInfo->font);
    title.setCharacterSize(25);
    title.setPosition(std::lroundf(Window::VWIDTH / 2), 20);
    auto ir = title.getLocalBounds();
    title.setOrigin(std::lroundf(ir.width / 2), std::lroundf(ir.height / 2));
    title.setFillColor(sf::Color::Black);

    player = Map::C_CROSS;
    moveMade = false;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            auto sr = crossTex.getSize();

            mapButtons[i][j].setTexture(crossTex);
            mapButtons[i][j].setPosition(
                    {(float) i * (layoutTex.getSize().x / 3.0f + 3.0f) + layout.getPosition().x - layout.getOrigin().x +
                     sr.x / 2,
                     (float) j * (layoutTex.getSize().y / 3.0f + 3.0f) + layout.getPosition().y - layout.getOrigin().y +
                     sr.y / 2});
            mapButtons[i][j].setOnclick([i, j, gameInfo, this] {
                if (player == gameInfo->me && !map.getAt(i, j) && !gameOver) {
                    moveMade = true;
                    toPlace = {i, j};
                }
            });
        }
    }
}

void GameScene::update(float delta) {
    if (moveMade) {
        sf::Packet sndPacket;
        sndPacket << toPlace.x;
        sndPacket << toPlace.y;
        sndPacket.endOfPacket();
        gameInfo->socket->send(sndPacket);
        map.setAt(toPlace.x, toPlace.y, player);

        if (player == Map::C_CROSS) player = Map::C_CIRCLE;
        else if (player == Map::C_CIRCLE) player = Map::C_CROSS;

        moveMade = false;
    }

    sf::Packet rcvPacket;
    if (gameInfo->socket->receive(rcvPacket) == sf::Socket::Status::Done) {
        int x, y;
        rcvPacket >> x;
        rcvPacket >> y;

        map.setAt(x, y, player);
        if (player == Map::C_CROSS) player = Map::C_CIRCLE;
        else if (player == Map::C_CIRCLE) player = Map::C_CROSS;
    }

    //TODO: implement a better way of reseting a game, eg. send a reset request and check to server and client, or a reset button
    if (gameOver) {
        time += delta;

        if (time > RESET_TIME) {
            time = 0;
            gameOver = false;
            moveMade = false;
            map.reset();
        }
    }
}

void GameScene::draw(std::shared_ptr<sf::RenderWindow> &window) {
    std::stringstream st;
    char winner = map.getWinner();

    //TODO: there are better ways to show this information
    if (winner == 0 && !map.isFull()) {
        st << "You: ";
        st << gameInfo->me;
        if (!gameOver) {
            if (gameInfo->me == player) st << "  -  Your turn";
            else st << "  -  Enemys turn";
        }
    } else {
        if (winner != 0) {
            if (gameInfo->me == winner) st << "You won!";
            else st << "You lost!";
        } else {
            st << "Draw!";
        }

        st << "  -  Reset in " << std::fixed << std::setprecision(1) << (RESET_TIME - time) << "s";
        gameOver = true;
    }

    title.setString(st.str());
    auto ir = title.getLocalBounds();
    title.setOrigin(std::lroundf(ir.width / 2), std::lroundf(ir.height / 2));

    window->draw(title);
    window->draw(layout);

    static sf::Sprite s;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            char c = map.getAt(i, j);

            if (c == Map::C_CROSS) s.setTexture(crossTex, true); //very inefficient, since we are binding them so often
            else if (c == Map::C_CIRCLE) s.setTexture(circleTex, true);
            else continue;

            s.setScale(0.9f, 0.9f);
            auto sr = s.getTexture()->getSize();
            s.setOrigin(sr.x / 2, sr.y / 2);
            s.setPosition((float) i * (layoutTex.getSize().x / 3.0f + 3.0f) + layout.getPosition().x -
                          layout.getOrigin().x + sr.x / 2,
                          (float) j * (layoutTex.getSize().y / 3.0f + 3.0f) + layout.getPosition().y -
                          layout.getOrigin().y + sr.y / 2);
            window->draw(s);
        }
    }
}

void GameScene::handle(sf::Event event) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Button::Left) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    mapButtons[i][j].mouseDown(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }
    }

    if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Button::Left) {
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    mapButtons[i][j].mouseUp(event.mouseButton.x, event.mouseButton.y);
                }
            }
        }

    }
}
