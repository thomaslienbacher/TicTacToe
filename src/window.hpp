//
// Created by Thomas Lienbacher on 13.09.2018.
//

#ifndef TICTACTOE_WINDOW_HPP
#define TICTACTOE_WINDOW_HPP

#include <memory>
#include <list>
#include <SFML/Window.hpp>
#include "eventhandler.hpp"

class Window {
    sf::Clock clock;
    sf::RenderWindow window;
    std::list<EventHandler *> eventHandlers;
    bool focused = true;

public:
    static constexpr unsigned int VWIDTH = 500;
    static constexpr unsigned int VHEIGHT = 500;

    explicit Window(std::string title);

    ~Window();

    float update(); //returns deltatime in seconds
    void prepare();

    void display();

    bool isRunning();

    bool isFocused() const;

    void addEventHandler(EventHandler *handler);

    sf::RenderWindow &getWindow();
};


#endif //TICTACTOE_WINDOW_HPP
