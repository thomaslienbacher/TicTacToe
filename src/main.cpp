#include "window.hpp"
#include "gamescene.hpp"
#include "menuscene.hpp"
#include "gameinfo.hpp"

int main() {
    GameInfo gameInfo;
    gameInfo.gamestate = MENU;

    Window window("Tic Tac Toe");

    MenuScene menuScene;
    GameScene gameScene;

    window.addEventHandler(&menuScene);

    while(window.isRunning()) {
        float delta = window.update();
        //update

        if(gameInfo.gamestate == MENU) {
            menuScene.update(delta);
        }
        if(gameInfo.gamestate == GAME) {

        }

        window.prepare();
        //render

        if(gameInfo.gamestate == MENU) {
            menuScene.draw(window.getWindow());
        }
        if(gameInfo.gamestate == GAME) {

        }

        window.display();
    }

    return 0;
}