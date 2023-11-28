#include <iostream>
#include <iomanip>
#include "Game.h"
#include <algorithm>


Game::Game(int columns, int rows, char symbol1, char symbol2) {
    numberOfColumns = columns;
    numberOfRows = rows;
    maxColumnCoordinate = 0;
    minColumnCoordinate = 0;
    maxRowCoordinate = 0;
    minRowCoordinate = 0;
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

void Game::printFirstLine(){
    std::cout << "    ";
    for(int i = 1; i <= numberOfColumns; i++){
        std::cout << setw(4) << i;
    }
    std::cout<< "\n";
}

void Game::printBoard() {
    system("Color 9");
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
    cout << endl;

}


void Game::mark(int x, int y) {
    board[y - 1][x - 1] = currentPlayer;
}

bool Game::checkFieldAvailability(int column, int row) {
    int columnIndex = column-1;
    int rowIndex = row-1;
    if(checkRange(column, row)){
      if(board[rowIndex][columnIndex] == emptyField){
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

void Game::setCheckerRange() {
    if(lastColumnPlayed < minColumnCoordinate){
        minColumnCoordinate = lastColumnPlayed;
    }else if(lastColumnPlayed > maxColumnCoordinate){
        maxColumnCoordinate = lastColumnPlayed;
    }

    if(lastRowPlayed < minRowCoordinate){
        minRowCoordinate = lastRowPlayed;
    }else if(lastRowPlayed > maxRowCoordinate){
        maxRowCoordinate = lastRowPlayed;
    }
}

bool Game::hasRowFiveSameSymbol() {
    int counter = 0;

    for(int i = minRowCoordinate-1; i < maxRowCoordinate; i++){
        for(int j = minColumnCoordinate-1; j < maxColumnCoordinate; j++){
            char currentCharacter = board[i][j];
            if (j+1 < maxColumnCoordinate) {
                char nextCharacter = board[i][j + 1];

                if (currentCharacter != emptyField) {
                    if (currentCharacter == nextCharacter) {
                        counter++;
                    } else {
                        counter = 0;
                    }
                }

                if (counter == 4) {
                    wonPlayerSymbol = currentCharacter;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Game::hasColumnSameSymbol() {
    int counter = 0;

        for(int j = minColumnCoordinate-1; j < maxColumnCoordinate; j++){
            for(int i = minRowCoordinate-1; i < maxRowCoordinate; i++){
            char currentCharacter = board[i][j];
            if (i+1 < maxRowCoordinate) {
                char nextCharacter = board[i + 1][j];

                if (currentCharacter != emptyField) {
                    if (currentCharacter == nextCharacter) {
                        counter++;
                    } else {
                        counter = 0;
                    }
                }

                if (counter == 4) {
                    wonPlayerSymbol = currentCharacter;
                    return true;
                }
            }
        }
    }

    return false;
}

bool Game::hasRightDiagonalSameSymbol() {
    int counter = 0;

    for(int i = minRowCoordinate-1; i < maxRowCoordinate; i++){
        for(int j = minColumnCoordinate-1; j < maxColumnCoordinate; j++){
            char currentCharacter = board[i][j];
            if (j+1 < maxColumnCoordinate && i+1 < maxRowCoordinate) {
                int num = 1;
                char nextCharacter = board[i + num][j + num];

                if (currentCharacter != emptyField) {
                    while(currentCharacter == nextCharacter){
                        counter++;
                        num++;
                        currentCharacter = nextCharacter;
                        nextCharacter = board[i + num][j + num];

                        cout<<"Current: " << currentCharacter<<endl;
                        cout<<"Next: " << nextCharacter<<endl;
                        cout<<"Counter: " << counter<<endl;

                        if (counter == 4) {
                            wonPlayerSymbol = currentCharacter;
                            return true;
                        }
                    }
                    counter = 0;
                }


            }
        }
    }

    return false;
}

bool Game::hasLeftDiagonalSameSymbol() {
    int counter = 0;

    for(int i = minRowCoordinate-1; i < maxRowCoordinate; i++){
        for(int j = minColumnCoordinate-1; j < maxColumnCoordinate; j++){
            char currentCharacter = board[i][j];
            if (i+1 < maxRowCoordinate && j-1 > minColumnCoordinate) {
                char nextCharacter = board[i + 1][j - 1];

                if (currentCharacter != emptyField) {
                    if (currentCharacter == nextCharacter) {
                        counter++;
                    } else {
                        counter = 0;
                    }
                }

                if (counter == 4) {
                    wonPlayerSymbol = currentCharacter;
                    return true;
                }
            }

        }
    }

    return false;
}

bool Game::hasWon() {
    setCheckerRange();

    if(hasRowFiveSameSymbol() ||
        hasColumnSameSymbol() ||
        hasRightDiagonalSameSymbol() ||
        hasLeftDiagonalSameSymbol()){
        printBoard();
        cout << "Player " << wonPlayerSymbol << " has won!" << endl;
        return true;
    }

    return false;
}

bool Game::getCoordinatesFromInput(const string& coordinates) {
    string::size_type loc = coordinates.find( '-', 0 );
    if( loc != string::npos )
    {
        int coor1 = stoi(coordinates.substr(0, loc));
        int coor2 = stoi(coordinates.substr (loc + 1));

        if (checkRange(coor1, coor2) && checkFieldAvailability(coor1, coor2)) {
            mark(coor1, coor2);
            lastColumnPlayed = coor1;
            lastRowPlayed = coor2;
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
    cout << endl;
    if (!getCoordinatesFromInput(input)) {
        getPlayerInput();
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


void Game::run() {
    bool isRunning = true;
    int stepCounter = 0;

    while (isRunning) {
        printBoard();
        getPlayerInput();
        if(stepCounter == 0){
            minRowCoordinate = lastRowPlayed;
            maxRowCoordinate = lastRowPlayed;
            minColumnCoordinate = lastColumnPlayed;
            maxColumnCoordinate = lastColumnPlayed;
        }
        stepCounter++;
        if (hasWon()) {
            break;
        }
        isFull();
        alternatePlayers();
    }
}
