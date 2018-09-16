//
// Created by Thomas Lienbacher on 14.09.2018.
//

#ifndef TICTACTOE_BUTTON_HPP
#define TICTACTOE_BUTTON_HPP


#include <functional>
#include "sfml.hpp"
#include "gameinfo.hpp"

class Button {
    static constexpr float DOWN_SCALE = 0.93f;

    std::string text;
    sf::Sprite sprite;
    sf::FloatRect bounds;
    std::function<void()> onclick;
    bool down;

public:
    Button(std::string text, sf::Texture texture, sf::FloatRect bounds, std::function<void()> onclick);

    void draw(sf::RenderWindow &window);
    void mouseDown(int x, int y);
    void mouseUp(int x, int y);
};


#endif //TICTACTOE_BUTTON_HPP
