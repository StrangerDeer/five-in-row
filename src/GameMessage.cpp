//
// Created by Bence on 30/11/2023.
//

#include "GameMessage.h"

string GameMessage::turnRoundMessage(const string &username) {
    return username + "'s round";
}

string GameMessage::wonMessage(const string& winningPlayerName) {
    return winningPlayerName + " has won!";
}

string GameMessage::nameQuestion(const int &number) {
    return "What is the player " + to_string(number) + "'s name?";
}

string GameMessage::typeSymbolMessage(const string &name) {
    return name + " please choose a symbol!";
}

string GameMessage::getFirstPlayer(const string &name, const char &symbol) {
    string playerSymbol(1, symbol);
    return "First player: " + name + " with " + playerSymbol;
}

string GameMessage::getSecondPlayer(const string &name, const char &symbol) {
    string playerSymbol(1, symbol);
    return "Second player: " + name + " with " + playerSymbol;
}

string GameMessage::startPlayerMessage(const string &name) {
    return "Start: " + name;
}
