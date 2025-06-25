#include "LookCommand.h"
#include "../Game.h"
#include <iostream>

bool LookCommand::Execute(Game& game, const vector<string>& args) {
    Room* room = game.GetCurrentRoom();
    if (room) {
        cout << room->GetName() << "\n";
        cout << room->GetDescription() << "\n";
        return true;
    }
    else {
        cout << "You are out of the boundaries of the map. Congrats!\n";
        return false;
    }
}