//
// Created by Thomas Lienbacher on 13.09.2018.
//

#include "map.hpp"

Map::Map() {
    reset();
}

bool Map::setAt(int x, int y, char type) {
    if(!map[x][y]) {
        map[x][y] = type;
        return true;
    }

    return false;
}

char Map::getAt(int x, int y) {
    return map[x][y];
}

char Map::getWinner() {
    //check horizontal and vertical
    for (int i = 0; i < 3; ++i) {
        if (map[i][0] == C_CIRCLE && map[i][1] == C_CIRCLE && map[i][2] == C_CIRCLE) return C_CIRCLE;
        if (map[0][i] == C_CIRCLE && map[1][i] == C_CIRCLE && map[2][i] == C_CIRCLE) return C_CIRCLE;
        if (map[i][0] == C_CROSS && map[i][1] == C_CROSS && map[i][2] == C_CROSS) return C_CROSS;
        if (map[0][i] == C_CROSS && map[1][i] == C_CROSS && map[2][i] == C_CROSS) return C_CROSS;
    }

    //check diagonal
    if (map[0][0] == C_CIRCLE && map[1][1] == C_CIRCLE && map[2][2] == C_CIRCLE) return C_CIRCLE;
    if (map[0][2] == C_CIRCLE && map[1][1] == C_CIRCLE && map[2][0] == C_CIRCLE) return C_CIRCLE;
    if (map[0][0] == C_CROSS && map[1][1] == C_CROSS && map[2][2] == C_CROSS) return C_CROSS;
    if (map[0][2] == C_CROSS && map[1][1] == C_CROSS && map[2][0] == C_CROSS) return C_CROSS;

    return 0;
}

void Map::reset() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            map[i][j] = 0;
        }
    }
}

bool Map::isFull() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if(!map[i][j]) return false;
        }
    }

    return true;
}