//
// Created by Thomas Lienbacher on 03.01.2019.
//

#include <iostream>
#include "board.hpp"
#include <snn.hpp>

void addBoard(std::vector<Board> &boards, Board &board);

int main() {
    std::vector<Board> boards;

    char e[3][3] = {{Board::EMPTY, Board::EMPTY, Board::EMPTY},
                    {Board::EMPTY, Board::EMPTY, Board::EMPTY},
                    {Board::EMPTY, Board::EMPTY, Board::EMPTY}};

    Board empty(e, Board::HUMAN);

    addBoard(boards, empty);


    std::vector<std::vector<double>> inputs, outputs;
    for (auto &b : boards) {
        if (b.whosTurn() == Board::AI) {
           auto p = b.toDatasetEntry();
           inputs.emplace_back(p.first);
           outputs.emplace_back(p.second);
        }
    }

    std::cout << "Started training on " << inputs.size() << std::endl;

    std::vector<unsigned int> topology = {9, 27, 27, 9};
    snn::Network network(topology, false);

    for (int j = 0; j < 30; ++j) {
        std::cout << "Epoch " << j << "..." << std::endl;
        network.train(inputs, outputs, 1, 0.5);
    }

    for (auto &b : boards) {
        if (b.whosTurn() == Board::AI) {
            auto p = b.toDatasetEntry();
            inputs.emplace_back(p.first);
            auto prediction = network.predict(p.first);

            for (int i = 0; i < 9; ++i) {
                std::cout << (prediction[i] - p.first[i]) << " ";
            }

            std::cout << std::endl;
        }
    }
}

void addBoard(std::vector<Board> &boards, Board &board) {
    std::vector<Board> here = board.getAllMovements();
    std::vector<Board> next;

    for (auto &b : here) {
        addBoard(next, b);
    }

    boards.insert(boards.end(), here.begin(), here.end());
    boards.insert(boards.end(), next.begin(), next.end());
}
