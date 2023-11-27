#include <iostream>
#include "Game.h"

Game::Game(int columns, int rows, char symbol1, char symbol2) {
    numberOfColumns = columns;
    numberOfRows = rows;
    player1Symbol = symbol1;
    player2Symbol = symbol2;
    currentPlayer = player1Symbol;
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

void Game::mark(int x, int y) {
    board[x - 1][y - 1] = currentPlayer;
}

bool Game::checkFieldAvailability(int column, int row) {
    int columnIndex = column-1;
    int rowIndex = row-1;
    if(checkRange(column, row)){
      if(board[columnIndex][rowIndex] == '.'){
          return true;
      }
    }
        return false;
}

bool Game::checkRange(int column, int row) {
    if(column <= numberOfColumns && column > 0 && row <= numberOfRows && row > 0){
        return true;
    }
    return false;
}

void Game::alternatePlayers() {
    if(currentPlayer == player1Symbol) currentPlayer = player2Symbol;
    else currentPlayer = player1Symbol;
}
