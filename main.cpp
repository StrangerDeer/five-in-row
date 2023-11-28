#include <iostream>
#include "src/Game.h"

using namespace std;

int main() {
    Game game(15, 15, 'X', 'O');
    game.run();
    return 0;
}
