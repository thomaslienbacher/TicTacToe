//
// Created by Thomas Lienbacher on 19.09.2018.
//

#ifndef TICTACTOE_TEXTINPUT_HPP
#define TICTACTOE_TEXTINPUT_HPP

#include "sfml.hpp"
#include <memory>

class TextInput {
    static constexpr float BLINK_TIME = 0.35f;
    static constexpr float PADDING = 6.0f;

    std::string raw;
    sf::Text text;
    sf::RectangleShape box;
    sf::IntRect size;
    float time = 0;
    bool showUnderscore = false;
    int maxchars = 20;
    bool entered = false;

public:
    TextInput() = default;

    void update(float delta);
    void handle(sf::Event &event);
    void draw(std::shared_ptr<sf::RenderWindow> &window);
    std::string getInput();

    void setFont(sf::Font &font);
    void setSize(sf::IntRect intRect);
    void setMaxchars(int maxchars);

    bool isEntered() const;
};


#endif //TICTACTOE_TEXTINPUT_HPP
