//
// Created by Thomas Lienbacher on 14.09.2018.
//

#include "button.hpp"
#include <cmath>

Button::Button(std::string text, sf::Texture texture, sf::Vector2f position, std::function<void()> onclick)
        : sprite(texture), onclick(onclick) {
    setText(text);
    sprite.setPosition(position);
}

void Button::draw(std::shared_ptr<sf::RenderWindow> &window) {
    if (down) {
        sprite.setScale(DOWN_SCALE, DOWN_SCALE);
        text.setScale(DOWN_SCALE, DOWN_SCALE);
    } else {
        sprite.setScale(1, 1);
        text.setScale(1, 1);
    }

    auto gb = text.getGlobalBounds();
    text.setPosition(std::lroundf(sprite.getPosition().x - gb.width / 2),
                     std::lroundf(sprite.getPosition().y - gb.height / 2));
    text.setFillColor(sf::Color::Black);

    window->draw(sprite);
    window->draw(text);
}

void Button::mouseDown(int x, int y) {
    if (getBounds().contains(x, y)) down = true;
}

void Button::mouseUp(int x, int y) {
    if (down && getBounds().contains(x, y)) {
        onclick();
    }

    down = false;
}

void Button::setFont(const sf::Font &font) {
    text.setFont(font);
}

void Button::setText(const std::string &text) {
    this->text.setString(text);
}

void Button::setTexture(const sf::Texture &texture) {
    sprite.setTexture(texture, true);
    auto &ir = sprite.getTextureRect();
    sprite.setOrigin(std::lroundf(ir.width / 2), std::lroundf(ir.height / 2));
}

const sf::FloatRect Button::getBounds() const {
    auto ir = sprite.getTextureRect();
    return {sprite.getPosition().x - sprite.getOrigin().x, sprite.getPosition().y - sprite.getOrigin().y,
            (float) ir.width, (float) ir.height};
}

void Button::setOnclick(const std::function<void()> &onclick) {
    Button::onclick = onclick;
}

void Button::setPosition(const sf::Vector2f &position) {
    sprite.setPosition(position);
}
