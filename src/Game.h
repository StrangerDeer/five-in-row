#ifndef CPP_FIVE_IN_A_ROW_GAME_H
#define CPP_FIVE_IN_A_ROW_GAME_H

#include <vector>
#include "Logger.h"
#include "Player.h"

using namespace std;

class Game {
private:
    vector<vector<char>> board;
    Player player1;
    Player player2;
    int numberOfColumns{};
    int numberOfRows{};
    int minRowCoordinate;
    int maxRowCoordinate;
    int minColumnCoordinate;
    int maxColumnCoordinate;
    char emptyField = '.';
    char coordinateSeparator = '-';
    vector<string> quitMessages = {"quit", "q"};
    char player1Symbol{};
    char player2Symbol{};
    char currentPlayer;
    char wonPlayerSymbol{};
    int lastColumnPlayed{};
    int lastRowPlayed{};
    Logger logger;
    void initializeBoard();
    bool checkRange(int column, int row) const;
    void alternatePlayers();
    bool checkFieldAvailability(int column, int row);
    void printFirstLine();
    void mark(int x, int y);
    bool getCoordinatesFromInput(const string& coordinates);
    void printBoard();
    void getPlayerInput(bool& isRunning);
    bool isFull();
    void setCheckerRange();
    bool hasRowFiveSameSymbol();
    bool hasColumnSameSymbol();
    bool hasRightDiagonalSameSymbol();
    bool hasLeftDiagonalSameSymbol();
    bool hasWon();
    bool isConvertibleToInt(const std::string& str);
    void startGame();

public:
    Game();
    void run();

};


#endif //CPP_FIVE_IN_A_ROW_GAME_H
