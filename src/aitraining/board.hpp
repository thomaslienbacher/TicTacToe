//
// Created by Thomas Lienbacher on 03.01.2019.
//

#ifndef TICTACTOE_BOARD_HPP
#define TICTACTOE_BOARD_HPP


#include <vector>
#include <ostream>

struct Move {
    int x, y;
};

class Board {
    char map[3][3];
    char current;

    int score(int depth);

    static int minimization(Board &board, int depth);

    static int maximization(Board &board, int depth);

public:
    static constexpr char HUMAN = 'X';
    static constexpr char AI = 'O';
    static constexpr char EMPTY = 0;

    Board(char map[3][3], char current);

    std::vector<Board> getAllMovements();

    friend std::ostream &operator<<(std::ostream &os, const Board &board);

    int getBestMove();

    std::pair<std::vector<double>, std::vector<double>> toDatasetEntry();

    char whosTurn();

    bool isFull();

    char hasWinner();

    void switchCurrent();

    void set(char val, int x, int y);
};


#endif //TICTACTOE_BOARD_HPP
