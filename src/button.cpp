//
// Created by Thomas Lienbacher on 14.09.2018.
//

#include "button.hpp"

Button::Button(std::string text, sf::Texture texture, sf::Vector2f position, std::function<void()> onclick)
: sprite(texture), position(position), onclick(onclick) {
    setText(text);
}

void Button::draw(std::shared_ptr<sf::RenderWindow> &window) {
    if(down) {
        sprite.setScale(DOWN_SCALE, DOWN_SCALE);
        text.setScale(DOWN_SCALE, DOWN_SCALE);
    }
    else {
        sprite.setScale(1, 1);
        text.setScale(1, 1);
    }

    auto gb = text.getGlobalBounds();
    sprite.setPosition(position.x, position.y);
    text.setPosition(position.x- gb.width / 2, position.y - gb.height / 2);
    text.setFillColor(sf::Color::Black);

    window->draw(sprite);
    window->draw(text);
}

void Button::mouseDown(int x, int y) {
    if(getBounds().contains(x, y)) down = true;
}

void Button::mouseUp(int x, int y) {
    if(down && getBounds().contains(x, y)) {
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

const sf::Sprite &Button::getSprite() const {
    return sprite;
}

void Button::setTexture(const sf::Texture &texture) {
    sprite.setTexture(texture, true);
    const sf::IntRect& ir = sprite.getTextureRect();
    sprite.setOrigin(ir.width / 2, ir.height / 2);
}

const sf::FloatRect Button::getBounds() const {
    const sf::IntRect& ir = sprite.getTextureRect();
    return {position.x - sprite.getOrigin().x, position.y - sprite.getOrigin().y, ir.width, ir.height};
}

const std::function<void()> &Button::getOnclick() const {
    return onclick;
}

void Button::setOnclick(const std::function<void()> &onclick) {
    Button::onclick = onclick;
}

const sf::Vector2f &Button::getPosition() const {
    return position;
}

void Button::setPosition(const sf::Vector2f &position) {
    Button::position = position;
}
