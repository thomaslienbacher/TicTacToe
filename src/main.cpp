#include "window.hpp"
#include "gamescene.hpp"
#include "menuscene.hpp"
#include "gameinfo.hpp"

int main() {
    GameInfo gameInfo;
    gameInfo.gamestate = MENU;

    Window window("Tic Tac Toe");

    MenuScene menuScene(&gameInfo);
    GameScene gameScene(&gameInfo);

    window.addEventHandler(&menuScene);
    window.addEventHandler(&gameScene);

    while(window.isRunning()) {
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