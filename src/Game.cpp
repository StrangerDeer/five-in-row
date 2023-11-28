#include <iostream>
#include <iomanip>
#include "Game.h"
#include <algorithm>


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

void Game::printFirstLine(){
    std::cout << "    ";
    for(int i = 1; i <= numberOfColumns; i++){
        std::cout << setw(4) << i;
    }
    std::cout<< "\n";
}

void Game::printBoard() {
    int i = 1;
    printFirstLine();
    for(const vector<char>& rows : board) {
        std::cout << setw(4) << i;
        for(char position : rows) {
            std::cout << setw(4) << position;
        }
        std::cout << std::endl;
        i++;
    }
}


void Game::mark(int x, int y) {
    board[y - 1][x - 1] = currentPlayer;
}

bool Game::checkFieldAvailability(int column, int row) {
    int columnIndex = column-1;
    int rowIndex = row-1;
    if(checkRange(column, row)){
      if(board[rowIndex][columnIndex] == '.'){
          return true;
      }
    }
    cout << "Coordinate is already taken" << endl;
    return false;
}

bool Game::checkRange(int column, int row) const {
    if(column <= numberOfColumns && column > 0 && row <= numberOfRows && row > 0){
        return true;
    }
    cout << "Coordinate is out of board range" << endl;
    return false;
}

void Game::alternatePlayers() {
    if (currentPlayer == player1Symbol) currentPlayer = player2Symbol;
    else currentPlayer = player1Symbol;
}

bool Game::getCoordinatesFromInput(const string& coordinates) {
    string::size_type loc = coordinates.find( '-', 0 );
    if( loc != string::npos )
    {
        int coor1 = stoi(coordinates.substr(0, loc));
        int coor2 = stoi(coordinates.substr (loc + 1));

        if (checkRange(coor1, coor2) && checkFieldAvailability(coor1, coor2)) {
            mark(coor1, coor2);
            return true;
        }
    } else {
        cout << "Invalid coordinates" << endl;
    }
    return false;
}

void Game::getPlayerInput() {
    cout << "Coordinates: ";
    string input;
    cin >> input;
    if (!getCoordinatesFromInput(input)) {
        getPlayerInput();
    }
}

void Game::run() {
    bool isRunning = true;

    while (isRunning) {
        printBoard();
        getPlayerInput();
        alternatePlayers();
    }
}

bool Game::isFull() {
    char empty = '.';
    for (auto & i : board) {
        if (std::find(i.begin(), i.end(), empty) != i.end()) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}
