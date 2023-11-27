#include <iostream>
#include "Game.h"

Game::Game(int columns, int rows) {
    numberOfColumns = columns;
    numberOfRows = rows;
    initializeBoard();
}

void Game::initializeBoard() {
    for (int i = 0; i < numberOfRows; i++) {
        vector<char> row = {};
        for (int j = 0; j < numberOfColumns; j++) {
            row.push_back('.');
        }
        board.push_back(row);
    }
}

void Game::printBoard() {
    for(const vector<char>& rows : board) {
        for(char position : rows) {
            std::cout << position << " ";
        }
        std::cout << std::endl;
    }
}
