//
// Created by Thomas Lienbacher on 13.09.2018.
//

#ifndef TICTACTOE_MAP_HPP
#define TICTACTOE_MAP_HPP


class Map {

    char map[3][3];

public:
    static constexpr char C_CROSS = 'X';
    static constexpr char C_CIRCLE = 'O';

    Map();

    bool setAt(int x, int y, char type);
    char getAt(int x, int y);
    char getWinner();
};


#endif //TICTACTOE_MAP_HPP
