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
            row.push_back(emptyField);
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
      if(board[columnIndex][rowIndex] == emptyField){
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

void Game::setCheckerRange(int currentX, int currentY) {
    if(currentX < minRowCoordinate){
        minRowCoordinate = currentX;
    }else if(currentX > maxColumnCoordinate){
        maxRowCoordinate = currentX;
    }

    if(currentY < minColumnCoordinate){
        minColumnCoordinate = currentY;
    }else if(currentY > maxColumnCoordinate){
        maxColumnCoordinate = currentY;
    }
}

bool Game::hasRowFiveSameSymbol() {
    int counter = 0;

    for(int i = minRowCoordinate; i <= maxRowCoordinate; i++){
        for(int j = minColumnCoordinate; j <= maxColumnCoordinate; j++){
            char currentCharacter = board[i][j];
            char nextCharacter = board[i][j + 1];

            if(currentCharacter != emptyField){
                if(currentCharacter == nextCharacter){
                    counter++;
                }else{
                    counter = 0;
                }
            }

            if(counter == 5){
                wonPlayerSymbol = currentCharacter;
                return true;
            }
        }
    }

    return false;
}

bool Game::hasWon(int currentX, int currentY) {
    setCheckerRange(currentX, currentY);

    if(hasRowFiveSameSymbol()){
        return true;
    }

    return false;
}
