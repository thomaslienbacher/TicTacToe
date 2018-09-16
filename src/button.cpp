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

void Button::draw(sf::RenderWindow &window) {
    if(down) {
        sprite.setScale(DOWN_SCALE, DOWN_SCALE);
    }
    else {
        sprite.setScale(1, 1);
    }

    window.draw(sprite);
}

void Button::mouseDown(int x, int y) {

}

void Button::mouseUp(int x, int y) {

}
