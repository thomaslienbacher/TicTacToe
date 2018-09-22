#include "window.hpp"
#include "gamescene.hpp"
#include "menuscene.hpp"

int main() {
    GameInfo gameInfo;
    gameInfo.gamestate = MENU;

    Window window("Tic Tac Toe");

    MenuScene menuScene(&gameInfo);
    GameScene gameScene(&gameInfo);

    window.addEventHandler(&menuScene);
    window.addEventHandler(&gameScene);

    gameInfo.font.loadFromFile("res/roboto.ttf");

    while(window.isRunning()) {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.getWindow()->close();

        float delta = window.update();
        //update

        if(gameInfo.gamestate == GAME) {
            gameScene.update(delta);
        }

        window.prepare();
        //render

        if(gameInfo.gamestate == MENU) {
            menuScene.draw(window.getWindow());
        }
        if(gameInfo.gamestate == GAME) {
            gameScene.draw(window.getWindow());
        }

        window.display();
    }

    return 0;
}