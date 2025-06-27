#include "DropCommand.h"
#include "../../Game.h"
#include "../../Room.h"
#include "../../Item.h"
#include <iostream>

map<int, string> DropCommand::GetPattern() const {
	return {
		{0, "drop"}
	};
}

bool DropCommand::Execute(Game& game, const vector<string>& args) {
    vector<Item*>& inventory = game.GetInventory();
    string target = args[1];

    if (target == "all") {
        if (inventory.empty()) {
            cout << "What do you want to drop those things in?\n";
            return false;
        }

        Room* current = game.GetCurrentRoom();
        for (Item* item : inventory) {
            inventory.erase(remove(inventory.begin(), inventory.end(), item), inventory.end());
            current->AddEntity(item);
            cout << item->GetName() +" : Dropped";
        }

        cout << "You drop everything.\n";
        inventory.clear();
        return true;
    }
    else {
        for (auto it = inventory.begin(); it != inventory.end(); ++it) {
            if ((*it)->GetName() == target) {
                Item* item = *it;
                inventory.erase(it);
                game.GetCurrentRoom()->AddEntity(item);
                std::cout << "Dropped.\n";
                return true;
            }
        }

        cout << "You can't see any such thing.\n";
        return false;
    }
}