#include "window.hpp"
#include "gameinfo.hpp"

int main() {
    Window window("Test Window");
    auto gameInfo = new GameInfo();

    while(window.isRunning()) {
        float delta = window.update();

        window.prepare();

        window.display();
    }

    delete gameInfo;

    return 0;
}