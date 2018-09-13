//
// Created by Thomas Lienbacher on 13.09.2018.
//

#ifndef TICTACTOE_WINDOW_HPP
#define TICTACTOE_WINDOW_HPP

#include <memory>
#include "sfml.hpp"

class Window {
    sf::Clock clock;
    std::shared_ptr<sf::RenderWindow> window;

public:
    static constexpr unsigned int VWIDTH = 600;
    static constexpr unsigned int VHEIGHT = 600;

    Window(std::string title);
    ~Window();

    float update(); //returns deltatime in seconds
    void prepare();
    void display();
    bool isRunning();

    const sf::Clock &getClock() const;

    const std::shared_ptr<sf::RenderWindow> &getWindow() const;
};


#endif //TICTACTOE_WINDOW_HPP
