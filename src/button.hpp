//
// Created by Thomas Lienbacher on 14.09.2018.
//

#ifndef TICTACTOE_BUTTON_HPP
#define TICTACTOE_BUTTON_HPP


#include <functional>
#include "sfml.hpp"
#include <memory>

class Button {

    static constexpr float DOWN_SCALE = 0.94f;

    sf::Sprite sprite;
    sf::Text text;
    sf::Vector2f position;
    std::function<void()> onclick;
    bool down = false;

public:
    Button() = default;
    Button(std::string text, sf::Texture texture, sf::Vector2f position, std::function<void()> onclick);

    void draw(std::shared_ptr<sf::RenderWindow> &window);
    void mouseDown(int x, int y);
    void mouseUp(int x, int y);

    void setFont(const sf::Font &font);
    void setText(const std::string &text);
    const sf::Sprite &getSprite() const;
    void setTexture(const sf::Texture &texture);
    const sf::Vector2f &getPosition() const;
    void setPosition(const sf::Vector2f &position);
    const sf::FloatRect getBounds() const;
    const std::function<void()> &getOnclick() const;
    void setOnclick(const std::function<void()> &onclick);
};


#endif //TICTACTOE_BUTTON_HPP
