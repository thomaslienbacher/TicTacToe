#include "window.hpp"
#include "gameinfo.hpp"
#include "logiccontroller.hpp"
#include "drawcontroller.hpp"

int main() {
    Window window("Test Window");
    auto gameInfo = new GameInfo();
    LogicController logicController(gameInfo);
    DrawController drawController(gameInfo);

    while(window.isRunning()) {
        float delta = window.update();
        logicController.logic(delta);
        window.prepare();
        drawController.draw(delta, window.getWindow());
        window.display();
    }

    delete gameInfo;

    return 0;
}