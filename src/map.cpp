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

#define X(x, y) map[x][y]==C_CROSS
#define O(x, y) map[x][y]==C_CIRCLE

char Map::getWinner() {
    //x winner
    if(X(0,0) && X(0,1) && X(0,2)) return C_CROSS;
    if(X(1,0) && X(1,1) && X(1,2)) return C_CROSS;
    if(X(2,0) && X(2,1) && X(2,2)) return C_CROSS;

    if(X(0,0) && X(1,0) && X(2,0)) return C_CROSS;
    if(X(0,1) && X(1,1) && X(2,1)) return C_CROSS;
    if(X(0,2) && X(1,2) && X(2,2)) return C_CROSS;

    if(X(0,0) && X(1,1) && X(2,2)) return C_CROSS;
    if(X(0,2) && X(1,1) && X(2,0)) return C_CROSS;

    //o winner
    if(O(0,0) && O(0,1) && O(0,2)) return C_CIRCLE;
    if(O(1,0) && O(1,1) && O(1,2)) return C_CIRCLE;
    if(O(2,0) && O(2,1) && O(2,2)) return C_CIRCLE;

    if(O(0,0) && O(1,0) && O(2,0)) return C_CIRCLE;
    if(O(0,1) && O(1,1) && O(2,1)) return C_CIRCLE;
    if(O(0,2) && O(1,2) && O(2,2)) return C_CIRCLE;

    if(O(0,0) && O(1,1) && O(2,2)) return C_CIRCLE;
    if(O(0,2) && O(1,1) && O(2,0)) return C_CIRCLE;

    return 0;
}

#undef X
#undef O

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