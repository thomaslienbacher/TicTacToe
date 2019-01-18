//
// Created by Thomas Lienbacher on 18.09.2018.
//

#ifndef TICTACTOE_ANIMATION_HPP
#define TICTACTOE_ANIMATION_HPP


#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

//this class isn't used but still included
class Animation {

    float swapTime;
    float time = 0;
    sf::Sprite sprite;
    int currentFrame = 0;
    std::vector<sf::IntRect> regions;

public:
    Animation() = default;

    Animation(float fps, sf::Texture &texture, int rows, int cols);

    void setFps(float fps);

    void setTexture(sf::Texture &texture, int rows, int cols);

    void setPosition(sf::Vector2f pos);

    void update(float delta);

    void draw(std::shared_ptr<sf::RenderWindow> &window);
};


#endif //TICTACTOE_ANIMATION_HPP
