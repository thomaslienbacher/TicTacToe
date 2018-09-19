//
// Created by Thomas Lienbacher on 19.09.2018.
//

#include "textinput.hpp"

void TextInput::update(float delta) {
    time += delta;

    if (time > BLINK_TIME) {
        time -= BLINK_TIME;
        showUnderscore = !showUnderscore;
    }
}

void TextInput::draw(std::shared_ptr<sf::RenderWindow> &window) {
    if (showUnderscore && raw.length() < maxchars) text.setString(raw + "_");
    else text.setString(raw);

    window->draw(box);
    window->draw(text);
}

void TextInput::handle(sf::Event &event) {
    if (event.type == sf::Event::TextEntered) {
        if (event.text.unicode < 128) {
            if (event.text.unicode == 8) { // backspace
                if (raw.length() > 0) raw = raw.substr(0, raw.size() - 1);
            } else if (event.text.unicode == 13) { // enter
                entered = true;
            } else {
                if (raw.length() < maxchars) raw += event.text.unicode;
            }
        }
    }
}

std::string TextInput::getInput() {
    return raw;
}

void TextInput::setFont(sf::Font &font) {
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
}

void TextInput::setSize(sf::IntRect intRect) {
    size = intRect;

    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color::Black);
    box.setOutlineThickness(5.0f);
    box.setPosition(size.left, size.top);
    box.setSize({size.width, size.height});

    text.setPosition(size.left + PADDING, size.top + size.height / 2 - text.getCharacterSize() / 2);
}

void TextInput::setMaxchars(int maxchars) {
    TextInput::maxchars = maxchars;
}

bool TextInput::isEntered() const {
    return entered;
}
