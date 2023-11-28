#include <iostream>
#include "src/Game.h"

using namespace std;

int main() {
    std::cout << "";
    Game game(10, 10, 'X', 'Y');
    game.run();
    return 0;
}
