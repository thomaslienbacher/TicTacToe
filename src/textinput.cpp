//
// Created by Thomas Lienbacher on 19.09.2018.
//

#include <iostream>
#include "textinput.hpp"
#include <cmath>

void TextInput::update(float delta) {
    time += delta;

    if (time > BLINK_TIME) {
        time -= BLINK_TIME;
        showUnderscore = !showUnderscore;
    }
}

void TextInput::draw(sf::RenderWindow &window) {
    if (text.getLocalBounds().width > (size.width - PADDING * 2)) {
        raw = raw.substr(0, raw.size() - 1);
        limitReached = true;
    }

    if (showUnderscore && canCharFit() && !limitReached) text.setString(raw + "_");
    else text.setString(raw);

    window.draw(box);
    window.draw(text);
}

//TODO: remove quick blink of protruding char
void TextInput::handle(sf::Event &event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {
            if (event.text.unicode == 8) { // backspace
                if (raw.length() > 0) raw = raw.substr(0, raw.size() - 1);
                limitReached = false;
            } else if (event.text.unicode == 13) { // enter
                entered = true;
            } else {
                if (canCharFit() && !limitReached) raw += (char) event.text.unicode;
            }
        }
    }
}

inline bool TextInput::canCharFit() {
    return text.getLocalBounds().width < (size.width - PADDING * 2);
}

std::string TextInput::getInput() {
    return raw;
}

void TextInput::setFont(sf::Font &font) {
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
}

void TextInput::setSize(sf::FloatRect floatRect) {
    size = floatRect;

    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(5.0f);
    box.setPosition(size.left, size.top);
    box.setSize({size.width, size.height});

    text.setPosition(std::lroundf(size.left + PADDING),
                     std::lroundf(size.top + size.height / 2 - text.getCharacterSize() / 2));
}

bool TextInput::isEntered() const {
    return entered;
}
