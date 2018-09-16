//
// Created by Thomas Lienbacher on 13.09.2018.
//

#include <iostream>
#include "window.hpp"

Window::Window(std::string title){
    window = std::make_shared<sf::RenderWindow>(sf::VideoMode(VWIDTH, VHEIGHT), title,
                                  sf::Style::Close, sf::ContextSettings(8,0,4,3,3));

    window->setFramerateLimit(30);
    window->setVerticalSyncEnabled(true);

    sf::Image icon;
    icon.loadFromFile("res/icon.png");
    window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

Window::~Window() {
    window->close();
}

float Window::update() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if(event.type == sf::Event::Closed) {
            window->close();
        }

        if(event.type == sf::Event::MouseButtonPressed) {
            std::cout << event.mouseButton.x << " " << event.mouseButton.y << " " << event.mouseButton.button << std::endl;
        }
    }

    return clock.restart().asSeconds();
}

void Window::prepare(){
    window->clear(sf::Color(175,175,175,255));
}

void Window::display() {
    window->display();
}

bool Window::isRunning() {
    return window->isOpen();
}

std::shared_ptr<sf::RenderWindow> &Window::getWindow() {
    return window;
}
