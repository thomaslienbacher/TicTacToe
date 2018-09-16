//
// Created by Thomas Lienbacher on 14.09.2018.
//

#include "button.hpp"

Button::Button(std::string text, sf::Texture texture, sf::FloatRect bounds, std::function<void()> onclick)
: text(text), sprite(texture), bounds(bounds), onclick(onclick) {
    sprite.setPosition(bounds.left, bounds.top);
    const sf::IntRect& ir = sprite.getTextureRect();
    sprite.setOrigin(ir.left + ir.width / 2, ir.top + ir.height / 2);
}

void Button::draw(std::shared_ptr<sf::RenderWindow> &window) {
    window->draw(sprite);
}

void Button::check(sf::Vector2i pos) {
    if(bounds.contains(pos.x, pos.y)){
        onclick();
    }
}

const std::string &Button::getText() const {
    return text;
}

void Button::setText(const std::string &text) {
    Button::text = text;
}

const sf::Sprite &Button::getSprite() const {
    return sprite;
}

void Button::setTexture(const sf::Texture &texture) {
    sprite.setTexture(texture, true);
}

const sf::FloatRect &Button::getBounds() const {
    return bounds;
}

void Button::setBounds(const sf::FloatRect &bounds) {
    Button::bounds = bounds;

    sprite.setPosition(bounds.left, bounds.top);
    const sf::IntRect& ir = sprite.getTextureRect();
    sprite.setOrigin(ir.left + ir.width / 2, ir.top + ir.height / 2);
}

const std::function<void()> &Button::getOnclick() const {
    return onclick;
}

void Button::setOnclick(const std::function<void()> &onclick) {
    Button::onclick = onclick;
}
