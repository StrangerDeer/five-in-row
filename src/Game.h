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
    bool checkRange(int column, int row) const;
    void alternatePlayers();
    bool checkFieldAvailability(int column, int row);
    void mark(int x, int y);
    bool getCoordinatesFromInput(const string& coordinates);
    void printBoard();
    void getPlayerInput();
    bool isFull();
public:
    Game(int columns, int rows, char symbol1, char symbol2);
    void run();
};


#endif //CPP_FIVE_IN_A_ROW_GAME_H
