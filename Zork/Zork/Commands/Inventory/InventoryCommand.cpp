#include "InventoryCommand.h"
#include <iostream>

map<int, string> InventoryCommand::GetPattern() const {
	return {
		{ 0, "inventory" }
	};
}

bool InventoryCommand::Execute(Game& game, const vector<string>& args) {
    vector<Item*> inventory = game.GetInventory();

    if (game.GetInventory().empty()) {
		cout << "You are empty handed." << endl;
	} else {
		cout << "You are carrying:" << endl;
		for (Item* item : inventory) {
			cout << "- " << item->GetName() << endl;
		}
	}
	return true;
}