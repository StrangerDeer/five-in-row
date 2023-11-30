//
// Created by Deer on 29/11/2023.
//

#ifndef CPP_FIVE_IN_A_ROW_PLAYER_H
#define CPP_FIVE_IN_A_ROW_PLAYER_H


#include <string>

using namespace std;

class Player {

public:
    string name;
    char symbol{};
    Player();
    Player(string name, char symbol);
};


#endif //CPP_FIVE_IN_A_ROW_PLAYER_H
