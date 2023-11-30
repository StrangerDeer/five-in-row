#include <iostream>
#include <iomanip>
#include "Game.h"
#include <algorithm>


Game::Game(){}

void Game::initializeBoard() {
    for (int i = 0; i < numberOfRows; i++) {
        vector<char> row = {};
        for (int j = 0; j < numberOfColumns; j++) {
            row.push_back(emptyField);
        }
        board.push_back(row);
    }
}

void Game::printFirstLine() const{
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
    board.at(y - 1).at(x - 1) = currentPlayer;
}

bool Game::checkFieldAvailability(int column, int row) {
    int columnIndex = column-1;
    int rowIndex = row-1;
    if(checkRange(column, row)){
      if(board[rowIndex][columnIndex] == emptyField){
          return true;
      }
    }
    logger.log(message.coordinateIsTaken);
    return false;
}

bool Game::checkRange(int column, int row) const {
    if(column <= numberOfColumns && column > 0 && row <= numberOfRows && row > 0){
        return true;
    }
    logger.log(message.coordinateOutOfRange);
    return false;
}

void Game::alternatePlayers() {
    if (currentPlayer == player1.symbol) {
        logger.log(message.turnRoundMessage(player2.name));
        currentPlayer = player2.symbol;
    } else {
        logger.log(message.turnRoundMessage(player1.name));
        currentPlayer = player1.symbol;
    };
}

bool Game::hasRowFiveSameSymbol() {
    int counter = 0;

    for(int i = 0; i < numberOfRows; i++){
        for(int j = 0; j < numberOfColumns; j++){
            char currentCharacter = board[i][j];
            if (j+1 < numberOfColumns) {
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

        for(int j = 0; j < numberOfColumns; j++){
            for(int i = 0; i < numberOfRows; i++){
            char currentCharacter = board[i][j];
            if (i+1 < numberOfRows) {
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

    for(int i = 0; i < numberOfRows; i++){
        for(int j = 0; j < numberOfColumns; j++){
            char currentCharacter = board.at(i).at(j);
            if (j+1 < numberOfColumns && i+1 < numberOfRows) {
                int num = 1;
                char nextCharacter = board.at(i + num).at(j + num);

                if (currentCharacter != emptyField) {
                    while(currentCharacter == nextCharacter && j+num < numberOfColumns &&  i+num < numberOfRows){
                        counter++;
                        num++;
                        currentCharacter = nextCharacter;

                        if(j+num < numberOfColumns &&  i+num < numberOfRows){
                            nextCharacter = board.at(i + num).at(j + num);
                        }

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

    for(int i = 0; i < numberOfRows; i++){
        for(int j = 0; j < numberOfColumns; j++){
            int num = 1;
            char currentCharacter = board.at(i).at(j);
            if (i + 1 < numberOfRows && j - 1 >= numberOfColumns) {
                char nextCharacter = board.at(i + num).at(j - num);

                if (currentCharacter != emptyField && i + num < numberOfRows && j - num >= numberOfColumns) {
                    while(currentCharacter == nextCharacter){
                        counter++;
                        num++;
                        currentCharacter = nextCharacter;

                        if(i + num < numberOfRows && j - num >= numberOfColumns){
                            nextCharacter = board.at(i + num).at(j - num);
                        }

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

    if(hasRowFiveSameSymbol() ||
        hasColumnSameSymbol() ||
        hasRightDiagonalSameSymbol() ||
        hasLeftDiagonalSameSymbol()){
        printBoard();
        if (wonPlayerSymbol == player1.symbol) {
            logger.log(message.wonMessage(player1.name));
        } else if (wonPlayerSymbol == player2.symbol) {
            logger.log(message.wonMessage(player2.name));
        }
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
            logger.log(message.invalidCoordinate);
        }
    } else {
        logger.log(message.invalidCoordinate);
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

void Game::getPlayerInput(string& userInput) {
    logger.log(message.baseCoordinate);
    cin >> userInput;
    if (find(quitMessages.begin(), quitMessages.end(), userInput) != quitMessages.end()) {
        logger.log(message.goodbye);
    } else if (!getCoordinatesFromInput(userInput)) {
        getPlayerInput(userInput);
    }
}

bool Game::isFull(const int& stepCounter) {
    if(maxStep == stepCounter){
        printBoard();
        logger.log(message.boardIsFull);
        return true;
    }
    return false;
}

bool Game::userInputContainsExitCommand(const string &input) {
    return find(quitMessages.begin(), quitMessages.end(), input) != quitMessages.end();
}

void Game::setBoard(string& userInput) {
    logger.log(message.welcome);
    logger.log(message.columnQuestion);
    cin >> userInput;

    while(!isConvertibleToInt(userInput)){
        logger.log(message.notNumber);
        logger.log(message.giveNumber);
        cin >> userInput;
    }

    numberOfColumns = stoi(userInput);

    logger.log(message.rowQuestion);
    cin >> userInput;

    while(!isConvertibleToInt(userInput)){
        logger.log(message.notNumber);
        logger.log(message.giveNumber);
        cin >> userInput;
    }

    numberOfRows = stoi(userInput);
    maxStep = numberOfColumns * numberOfRows;
}

void Game::setPlayer(string& userInput) {
    int counter = 1;

    while(counter <= 2){
        logger.log(message.nameQuestion(counter));
        cin>> userInput;

        while(userInputContainsExitCommand(userInput)){
            logger.log(message.commandIsForbidden);
            cin>> userInput;
        }

        if(counter == 1) {
            player1.setUsername(userInput);
        } else {
            player2.setUsername(userInput);
        }

        logger.log(message.typeSymbolMessage(userInput));
        cin >> userInput;

        while(userInputContainsExitCommand(userInput)){
            logger.log(message.commandIsForbidden);
            cin>> userInput;
        }

        if(counter == 1){
            player1.setSymbol(userInput.at(0));
        } else {
            player2.setSymbol(userInput.at(0));
        }

        counter++;
    }

}

void Game::makeBoarEmpty() {
    for(int i = 0; i < board.size(); i++){
        vector<char> currentRow = board.at(i);
        for(int j = 0; j < currentRow.size(); j++){
            char currentField = board.at(i).at(j);
            if(currentField != emptyField){
                board.at(i).at(j) = emptyField;
            };
        };
    };
}

void Game::startGame() {
        string userInput;

        setBoard(userInput);
        setPlayer(userInput);
        currentPlayer = player1.symbol;
        logger.log(message.getFirstPlayer(player1.name, player1.symbol));
        logger.log(message.getSecondPlayer(player2.name, player2.symbol));
        logger.log(message.startPlayerMessage(player1.name));
        initializeBoard();
}


void Game::midGame() {
    string userInput;
    bool isRunning = true;
    int stepCounter = 0;

    while (isRunning) {
        printBoard();

        getPlayerInput(userInput);

        if(userInputContainsExitCommand(userInput)){
            logger.log(message.goodbye);
            break;
        }

        stepCounter++;
        if (hasWon() || isFull(stepCounter)) {
            logger.log(message.anotherRoundMessage);
            cin >> userInput;

            if(userInputContainsExitCommand(userInput)){
                logger.log(message.goodbye);
                break;
            } else {
                isRunning = false;
                makeBoarEmpty();
                currentPlayer = player1.symbol;
                logger.log(message.startPlayerMessage(player1.name));
                midGame();
            }
        }
        alternatePlayers();
    }
}

void Game::run() {
    startGame();
    midGame();
}




