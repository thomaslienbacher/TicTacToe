//
// Created by Thomas Lienbacher on 18.09.2018.
//

#include "animation.hpp"

Animation::Animation(float fps, sf::Texture &texture, int rows, int cols) {
    swapTime = 1.0f/fps;
    setTexture(texture, rows, cols);
}

void Animation::update(float delta) {
    time += delta;
}

void Animation::draw(std::shared_ptr<sf::RenderWindow> &window) {
    if(time > swapTime) {
        //next frame
        time -= swapTime;
        currentFrame++;
        if(currentFrame == regions.size()) currentFrame = 0;

        sprite.setTextureRect(regions[currentFrame]);
    }

    window->draw(sprite);
}

void Animation::setFps(float fps) {
    swapTime = 1.0f/fps;
}

void Animation::setTexture(sf::Texture &texture, int rows, int cols) {
    sprite.setTexture(texture);
    int w = (int)texture.getSize().x / cols;
    int h = (int)texture.getSize().y / rows;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            regions.push_back({w * j, h * i, w, h});
        }
    }

    sprite.setTextureRect(regions[0]);
    currentFrame = 0;
    time = 0;
}

void Animation::setPosition(sf::Vector2f pos) {
    sprite.setPosition(pos);
}
