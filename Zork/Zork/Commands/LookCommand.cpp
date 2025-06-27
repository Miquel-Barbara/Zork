#include "LookCommand.h"
#include "../Game.h"
#include <iostream>
#include "../Room.h"
#include "../Entity.h"

map<int, string> LookCommand::GetPattern() const {
    return {
        {0, "look"}
    };
}


bool LookCommand::Execute(Game& game, const vector<string>& args) {
    Room* room = game.GetCurrentRoom();

    if (room) {
        cout << room->GetName() << "\n";
        cout << room->GetDescription() << "\n";
        for (Entity* entity : room->GetEntities()) {
            cout << entity->GetDescription() << "\n";
        }
        return true;
    }
    else {
        cout << "You are out of the boundaries of the map. Congrats!\n";
        return false;
    }
}