#ifndef CPP_FIVE_IN_A_ROW_GAME_H
#define CPP_FIVE_IN_A_ROW_GAME_H

#include <vector>
using namespace std;
class Game {
private:
    vector<vector<char>> board;
    int numberOfColumns;
    int numberOfRows;
    char player1Symbol;
    char player2Symbol;
    char currentPlayer;
    void initializeBoard();
    bool checkRange(int column, int row);
    void alternatePlayers();
    bool checkFieldAvailability(int column, int row);
    void printFirstLine();
public:
    Game(int columns, int rows, char symbol1, char symbol2);
    void printBoard();
    void mark(int x, int y);
};


#endif //CPP_FIVE_IN_A_ROW_GAME_H
