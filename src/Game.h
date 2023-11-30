#ifndef CPP_FIVE_IN_A_ROW_GAME_H
#define CPP_FIVE_IN_A_ROW_GAME_H

#include <vector>
#include <cdonts.h>
#include "Logger.h"
#include "Player.h"
#include "GameMessage.h"

using namespace std;

class Game {
private:
    vector<vector<char>> board;
    Player player1;
    Player player2;
    GameMessage message;
    int maxStep;
    int numberOfColumns;
    int numberOfRows;
    const char emptyField = '.';
    const char coordinateSeparator = '-';
    vector<string> quitMessages = {"quit", "q"};
    char currentPlayer;
    char wonPlayerSymbol;
    int lastColumnPlayed;
    int lastRowPlayed;
    Logger logger;
    void initializeBoard();
    bool checkRange(int column, int row) const;
    void alternatePlayers();
    bool checkFieldAvailability(int column, int row);
    void printFirstLine() const;
    void mark(int x, int y);
    bool getCoordinatesFromInput(const string& coordinates);
    void printBoard();
    void getPlayerInput(string& userInput);
    bool isFull(const int& stepCounter);
    bool hasRowFiveSameSymbol();
    bool hasColumnSameSymbol();
    bool hasRightDiagonalSameSymbol();
    bool hasLeftDiagonalSameSymbol();
    bool hasWon();
    bool userInputContainsExitCommand(const string& input);
    void setBoard(string& userInput);
    void setPlayer(string& userInput);
    void midGame();
    void makeBoarEmpty();
    bool isConvertibleToInt(const std::string& str);
    void startGame();

public:
    Game();
    void run();
};


#endif //CPP_FIVE_IN_A_ROW_GAME_H
