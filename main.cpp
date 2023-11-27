#include <iostream>
#include "src/Game.h"

using namespace std;

int main() {
    Game game(5, 10, 'Y', 'X');
    game.mark(2,2);
    game.printBoard();
    return 0;
}
