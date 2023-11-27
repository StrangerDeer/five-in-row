#ifndef CPP_FIVE_IN_A_ROW_GAME_H
#define CPP_FIVE_IN_A_ROW_GAME_H

#include <vector>

using namespace std;
class Game {
private:
    vector<vector<char>> board;
    int numberOfColumns;
    int numberOfRows;
    void initializeBoard();

public:
    Game(int columns, int rows);
    void printBoard();
};


#endif //CPP_FIVE_IN_A_ROW_GAME_H
