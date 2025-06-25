#include "MoveCommand.h"
#include "../Game.h"
#include "../Direction.h"
#include <iostream>

bool MoveCommand::Execute(Game& game, const vector<string>& args) {
    if (args.size() < 2) {
        return false;
    }

    Direction dir = StringToDirection(args[1]);
    Room* current = game.GetCurrentRoom();
    Room* next = current->GetConnectedRoom(dir);

    if (next) {
        game.SetCurrentRoom(next);
        return true;
    }
    else {
        return false;
    }
}