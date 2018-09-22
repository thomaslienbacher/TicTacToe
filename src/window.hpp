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
    std::shared_ptr<sf::RenderWindow> window;
    std::list<EventHandler*> eventHandlers;

public:
    static constexpr unsigned int VWIDTH = 500;
    static constexpr unsigned int VHEIGHT = 500;

    Window(std::string title);
    ~Window();

    float update(); //returns deltatime in seconds
    void prepare();
    void display();
    bool isRunning();

    void addEventHandler(EventHandler *handler);

    std::shared_ptr<sf::RenderWindow> &getWindow();
};


#endif //TICTACTOE_WINDOW_HPP
