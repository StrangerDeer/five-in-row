//
// Created by Deer on 29/11/2023.
//

#include "Player.h"

#include <utility>

Player::Player() = default;

void Player::setUsername(string username) {
    name = std::move(username);
}

void Player::setSymbol(char symbol) {
    Player::symbol = symbol;
}
