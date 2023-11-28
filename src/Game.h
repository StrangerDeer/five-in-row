#ifndef CPP_FIVE_IN_A_ROW_GAME_H
#define CPP_FIVE_IN_A_ROW_GAME_H

#include <vector>
using namespace std;
class Game {
private:
    vector<vector<char>> board;
    int numberOfColumns;
    int numberOfRows;
    int minRowCoordinate;
    int maxRowCoordinate;
    int minColumnCoordinate;
    int maxColumnCoordinate;
    char emptyField = '.';
    char player1Symbol;
    char player2Symbol;
    char currentPlayer;
    char wonPlayerSymbol;
    void initializeBoard();
    bool checkRange(int column, int row);
    void alternatePlayers();
    bool checkFieldAvailability(int column, int row);
    void setCheckerRange(int currentX, int currentY);
    bool hasRowFiveSameSymbol();
    bool hasWon(int currentX, int currentY);
    void printBoard();
    void mark(int x, int y);
public:
    Game(int columns, int rows, char symbol1, char symbol2);
};


#endif //CPP_FIVE_IN_A_ROW_GAME_H
