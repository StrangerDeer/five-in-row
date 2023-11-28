#include <iostream>
#include "src/Game.h"

using namespace std;

int main() {
    Game game(10, 10, 'X', 'O');
    game.run();
    return 0;
}
