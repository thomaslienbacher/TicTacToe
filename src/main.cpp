#include "window.hpp"
#include "gamescene.hpp"
#include "menuscene.hpp"

enum State {MENU, GAME};

int main() {
    State gamestate = MENU;
    Window window("Tic Tac Toe");


    MenuScene menuScene;
    GameScene gameScene;

    window.addEventHandler(&menuScene);

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