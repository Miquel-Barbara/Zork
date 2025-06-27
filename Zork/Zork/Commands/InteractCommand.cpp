#include "InteractCommand.h"
#include "../Game.h"
#include "../Room.h"
#include <iostream>

map<int, string> InteractCommand::GetPattern() const {
	return {
		{0, "interact"},
		{1, "use"},
		{2, "examine"}
	};
}

bool InteractCommand::Execute(Game& game, const vector<string>& args) {
    if (args.size() < 2) {
        return false;
    }

    string verb = args[0];
    string target;

    for (size_t i = 1; i < args.size(); ++i) {
        if (!target.empty()) target += " ";
        target += args[i];
    }

    Room* currentRoom = game.GetCurrentRoom();
    if (!currentRoom) {
        cout << "You are nowhere. There's nothing to interact with." << std::endl;
        return false;
    }

    /*if (!currentRoom->TryExecuteAction(verb, target, game)) {
        cout << "You can't " << verb << " the " << target << "." << std::endl;
    }*/

    return true;
}