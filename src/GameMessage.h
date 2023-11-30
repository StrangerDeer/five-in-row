//
// Created by Bence on 30/11/2023.
//

#ifndef CPP_FIVE_IN_A_ROW_GAMEMESSAGE_H
#define CPP_FIVE_IN_A_ROW_GAMEMESSAGE_H

#include <string>

using namespace std;

class GameMessage {

public:
    const string coordinateIsTaken = "Coordinate is already taken";
    const string coordinateOutOfRange = "Coordinate is out of board range";
    const string invalidCoordinate = "Invalid coordinates";
    const string baseCoordinate = "Coordinates: ";
    const string welcome = "Hello!";
    const string goodbye = "Good Bye!";
    const string columnQuestion = "How many columns do you want?";
    const string rowQuestion = "How many rows do you want?";
    const string boardIsFull = "Board is full";
    const string notNumber = "It is not a number";
    const string giveNumber = "Please give me number!";
    const string commandIsForbidden = "This is command at the game. Please change it!";
    const string anotherRoundMessage = "Another round?";
    string turnRoundMessage(const string& username);
    string wonMessage(const char& wonPlayerSymbol);
    string nameQuestion(const int& number);
    string typeSymbolMessage(const string& name);
    string getFirstPlayer(const string& name, const char& symbol);
    string getSecondPlayer(const string& name, const char& symbol);
    string startPlayerMessage(const string& name);
};


#endif //CPP_FIVE_IN_A_ROW_GAMEMESSAGE_H
