#include <iostream>
#include "src/Game.h"

using namespace std;

int main() {
    Game game(5, 10, 'X', 'Y');
    game.run();
    return 0;
}
