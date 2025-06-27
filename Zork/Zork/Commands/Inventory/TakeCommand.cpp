#include "TakeCommand.h"
#include "../../Game.h"
#include "../../Room.h"
#include "../../Item.h"
#include <iostream>


map<int, string> TakeCommand::GetPattern() const {
	return {
		{0, "take"},
	};
}

bool TakeCommand::Execute(Game& game, const vector<string>& args) {
    string itemName = args[0];
    Room* current = game.GetCurrentRoom();
    vector<Entity*> entities = current->GetEntities();

    //Check if the item exists in the room
    Item* item = nullptr;
    for (Entity* entity : entities) {
		if (entity->GetName() == itemName) {
			item = dynamic_cast<Item*>(entity);
			if (item) {
				break;
			}
		}
	}
    
    if (item) {
        game.GetInventory().push_back(item);
        current->RemoveEntity(item);
        cout << "Taken.\n" << endl;
        return true;
    }
    else {
        cout << "You can't see any such thing.\n" << endl;
        return false;
    }
}