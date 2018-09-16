#include "window.hpp"
#include "gamescene.hpp"
#include "menuscene.hpp"

int main() {
    State gamestate = MENU;
    Window window("Tic Tac Toe");

    GameInfo gameInfo;
    gameInfo.window = &window;
    gameInfo.gamestate = &gamestate;

    MenuScene menuScene(&gameInfo);
    GameScene gameScene(&gameInfo);

    while(window.isRunning()) {
        float delta = window.update();
        //update

        if(gamestate == MENU) {
            menuScene.update(delta);
        }
        if(gamestate == GAME) {

        }

        window.prepare();
        //render

        if(gamestate == MENU) {
            menuScene.draw(window.getWindow());
        }
        if(gamestate == GAME) {

        }

        window.display();
    }

    return 0;
}