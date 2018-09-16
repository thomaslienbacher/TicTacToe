//
// Created by Thomas Lienbacher on 14.09.2018.
//

#ifndef TICTACTOE_BUTTON_HPP
#define TICTACTOE_BUTTON_HPP


#include <functional>
#include "sfml.hpp"
#include "gameinfo.hpp"

class Button {

    std::string text;
    sf::Sprite sprite;
    sf::FloatRect bounds;
    std::function<void()> onclick;

public:
    Button() = default;
    Button(std::string text, sf::Texture texture, sf::FloatRect bounds, std::function<void()> onclick);

    void draw(std::shared_ptr<sf::RenderWindow> &window);
    void check(sf::Vector2i pos);

    const std::string &getText() const;
    void setText(const std::string &text);
    const sf::Sprite &getSprite() const;
    void setTexture(const sf::Texture &texture);
    const sf::FloatRect &getBounds() const;
    void setBounds(const sf::FloatRect &bounds);
    const std::function<void()> &getOnclick() const;
    void setOnclick(const std::function<void()> &onclick);
};


#endif //TICTACTOE_BUTTON_HPP
