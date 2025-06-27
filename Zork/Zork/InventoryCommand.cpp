#include "InventoryCommand.h"
#include "Game.h"

InventoryCommand::Execute(Game& game, const vector<string>& args) {
	vector<Item*> inventory = game.GetInventory();
	if (inventory.empty()) {
		cout << "You are empty handed." << endl;
	} else {
		cout << "You are carrying:" << endl;
		for (const auto& item : inventory) {
			cout << "- " << item->GetName() << endl;
		}
	}
	return true;
}