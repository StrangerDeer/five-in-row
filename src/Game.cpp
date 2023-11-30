#include <iostream>
#include <iomanip>
#include "Game.h"
#include <algorithm>


Game::Game() {
    maxColumnCoordinate = 0;
    minColumnCoordinate = 0;
    maxRowCoordinate = 0;
    minRowCoordinate = 0;
    currentPlayer = player1Symbol;
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
    logger.log("Coordinate is already taken");
    return false;
}

bool Game::checkRange(int column, int row) const {
    if(column <= numberOfColumns && column > 0 && row <= numberOfRows && row > 0){
        return true;
    }
    logger.log("Coordinate is out of board range");
    return false;
}

void Game::alternatePlayers() {
    if (currentPlayer == player1Symbol) currentPlayer = player2Symbol;
    else currentPlayer = player1Symbol;
}

void Game::setCheckerRange() {
    minColumnCoordinate = 1;
    minRowCoordinate = 1;
    maxColumnCoordinate = numberOfColumns;
    maxRowCoordinate = numberOfRows;
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
                } else {
                    counter = 0;
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
                } else {
                    counter = 0;
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

                        if (counter == 4) {
                            wonPlayerSymbol = currentCharacter;
                            return true;
                        }
                    }
                    counter = 0;
                } else {
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
            int num = 1;
            char currentCharacter = board[i][j];
            if (i+1 < maxRowCoordinate && j-1 > minColumnCoordinate) {
                char nextCharacter = board[i + num][j - num];

                if (currentCharacter != emptyField) {
                    while(currentCharacter == nextCharacter){
                        counter++;
                        num++;
                        currentCharacter = nextCharacter;
                        nextCharacter = board[i + num][j - num];

                        if (counter == 4) {
                            wonPlayerSymbol = currentCharacter;
                            return true;
                        }
                    }
                    counter = 0;
                } else {
                    counter = 0;
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
    string::size_type loc = coordinates.find( coordinateSeparator, 0 );
    if( loc != string::npos )
    {
        string c1 = coordinates.substr(0, loc);
        string c2 = coordinates.substr (loc + 1);

        if (isConvertibleToInt(c1) && isConvertibleToInt(c2)) {
            int coord1 = stoi(c1);
            int coord2 = stoi(c2);
            if (checkRange(coord1, coord2) && checkFieldAvailability(coord1, coord2)) {
                mark(coord1, coord2);
                lastColumnPlayed = coord1;
                lastRowPlayed = coord2;
                return true;
            }
        } else {
            logger.log("Invalid coordinates");
        }
    } else {
        logger.log("Invalid coordinates");
    }
    return false;
}

bool Game::isConvertibleToInt(const std::string& str) {
    try {
        std::stoi(str);
        return true;
    } catch (...) {
        return false;
    }
}

void Game::getPlayerInput(bool& isRunning) {
    logger.log("Coordinates: ");
    string input;
    cin >> input;
    cout << endl;
    if (find(quitMessages.begin(), quitMessages.end(), input) != quitMessages.end()) {
        logger.log("Good Bye");
        isRunning = false;
    } else if (!getCoordinatesFromInput(input)) {
        getPlayerInput(isRunning);
    }
}


bool Game::isFull() {
    for (auto & i : board) {
        if (std::find(i.begin(), i.end(), emptyField) != i.end()) {
            return false;
        } else {
            return true;
        }
    }
    return false;
}

void Game::startGame() {
        string userInput;
        logger.log("Hello");
        logger.log("How many columns do you want?");
        cin >> userInput;

        while(!isConvertibleToInt(userInput)){
            logger.log("It is not a number");
            logger.log("Please give me a number");
            cin >> userInput;
        }

        numberOfColumns = stoi(userInput);

        logger.log("How many rows do you want?");
        cin >> userInput;

        while(!isConvertibleToInt(userInput)){
            logger.log("It is not a number");
            logger.log("Please give me a number");
            cin >> userInput;
        }

        numberOfRows = stoi(userInput);

        string username;
        char symbol;

        logger.log("What is the player 1 name?");
        cin>> userInput;
        username = userInput;
        logger.log(username + " please type a symbol!");
        cin >> userInput;
        symbol = userInput.at(0);
        player1 = new Player(username, symbol);

        logger.log("What is the player 2 name?");
        cin>> userInput;
        username = userInput;
        logger.log(username + " please type a symbol!");
        cin >> userInput;
        symbol = userInput.at(0);
        player2 = new Player(username, symbol);

        logger.log("First player: " + player1.name + " with " + player1.symbol);
        logger.log("Second player: " + player2.name + " with " + player2.symbol);
        logger.log("Start: " + player1.name);
        initializeBoard();
}

void Game::run() {
    startGame();
    bool isRunning = true;
    int stepCounter = 0;

    while (isRunning) {
        printBoard();
        getPlayerInput(isRunning);
        stepCounter++;
        if (hasWon()) {
            break;
        }
        isFull();
        alternatePlayers();
    }
}
