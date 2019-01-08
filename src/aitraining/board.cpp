//
// Created by Thomas Lienbacher on 03.01.2019.
//

#include <sstream>
#include <iostream>
#include <utility>
#include <vector>
#include "board.hpp"

Board::Board(char map[3][3], char current) : current(current) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            this->map[i][j] = map[i][j];
        }
    }
}

std::vector<Board> Board::getAllMovements() {
    std::vector<Board> next;

    //if (hasWinner() || isFull()) return next;             //uncomment this line to also include finished games
    char newPlayer = current == HUMAN ? AI : HUMAN;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (map[i][j] == EMPTY) {
                Board a(map, current);
                a.map[i][j] = current;
                if (a.isFull() || a.hasWinner()) continue;   //comment this line to also include finished games

                a.current = newPlayer;
                next.emplace_back(a);
            }
        }
    }

    return next;
}

int Board::getBestMove() {
    Move best = {-1, -1};
    int score = -1000;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (map[i][j] == EMPTY) {
                Board a(map, AI);
                a.map[i][j] = AI;
                int s = minimization(a, 0);

                if (s > score) {
                    score = s;
                    best.x = i;
                    best.y = j;
                }
            }
        }
    }

    return best.x + best.y * 3;
}

int Board::minimization(Board &board, int depth) {
    if (board.hasWinner() || board.isFull())
        return board.score(depth);

    int score = 1000;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.map[i][j] == EMPTY) {
                Board a(board.map, AI);
                a.map[i][j] = AI;
                int s = maximization(a, depth + 1);

                if (s < score) {
                    score = s;
                }
            }
        }
    }

    return score;
}

int Board::maximization(Board &board, int depth) {
    if (board.hasWinner() || board.isFull())
        return board.score(depth);

    int score = -1000;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board.map[i][j] == EMPTY) {
                Board a(board.map, HUMAN);
                a.map[i][j] = HUMAN;
                int s = minimization(a, depth + 1);

                if (s > score) {
                    score = s;
                }
            }
        }
    }

    return score;
}

int Board::score(int depth) {
    int score = 0;
    if (hasWinner() == HUMAN) score = -20 + depth;
    if (hasWinner() == AI) score = 20 - depth;
    return score;
}

std::pair<std::vector<double>, std::vector<double>> Board::toDatasetEntry() {
    std::vector<double> inputs, outputs;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            double p = 0;
            if (map[i][j] == AI) p = 1.0;
            if (map[i][j] == HUMAN) p = -1.0;

            inputs.emplace_back(p);
        }
    }

    int best = getBestMove();

    for (int k = 0; k < 9; ++k) {
        if(k == best) outputs.emplace_back(1);
        else outputs.emplace_back(0);
    }

    return std::make_pair(inputs, outputs);
}

bool Board::isFull() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (map[i][j] == EMPTY) return false;
        }
    }

    return true;
}

char Board::hasWinner() {
    //check vertical and horizontal
    for (int i = 0; i < 3; ++i) {
        if (map[i][0] == HUMAN && map[i][1] == HUMAN && map[i][2] == HUMAN) return HUMAN;
        if (map[0][i] == HUMAN && map[1][i] == HUMAN && map[2][i] == HUMAN) return HUMAN;
        if (map[i][0] == AI && map[i][1] == AI && map[i][2] == AI) return AI;
        if (map[0][i] == AI && map[1][i] == AI && map[2][i] == AI) return AI;
    }

    //check diagonal
    if (map[0][0] == HUMAN && map[1][1] == HUMAN && map[2][2] == HUMAN) return HUMAN;
    if (map[0][2] == HUMAN && map[1][1] == HUMAN && map[2][0] == HUMAN) return HUMAN;
    if (map[0][0] == AI && map[1][1] == AI && map[2][2] == AI) return AI;
    if (map[0][2] == AI && map[1][1] == AI && map[2][0] == AI) return AI;

    return EMPTY;
}

std::ostream &operator<<(std::ostream &os, const Board &board) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            char c = board.map[i][j];
            os << (c == 0 ? '-' : c) << " ";
        }
        os << std::endl;
    }

    return os;
}

char Board::whosTurn() {
    return current;
}

void Board::set(char val, int x, int y) {
    map[x][y] = val;
}

void Board::switchCurrent() {
    current = current == AI ? HUMAN : AI;
}
