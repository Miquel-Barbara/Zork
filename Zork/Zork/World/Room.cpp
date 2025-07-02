#include "Room.h"
#include "Exit.h"
#include "RestrictedExit.h"
#include "../Objects/Object.h"
#include "../Objects/Container.h"
#include <random> 
#include <ctime>

Room::Room(const string& name, const string& description): Entity(name, description) {}

void Room::AddExit(Exit* exit) {
	if (exit != nullptr) {
		exits.push_back(exit);
	}
}

void Room::RemoveExit(Exit* exit) {
	auto it = std::find(exits.begin(), exits.end(), exit);
	if (it != exits.end()) {
		exits.erase(it);
	}
}

Exit* Room::GetExit(Direction direction) const {
	for (const auto& exit : exits) {
		if (exit->GetDirection() == direction) {
			return exit;
		}
	}
	return nullptr;
}

vector<Exit*> Room::GetExits() const {
	return exits;
}

void Room::DescribeAll() const {
	cout << GetName() << endl;
	cout << GetDescription();

	// Display special exits in the room
	for (Exit* exit : GetExits()) {
		RestrictedExit* restExit = dynamic_cast<RestrictedExit*>(exit);
		if (restExit) {
			cout << restExit->GetDescription();
		}
	}

	cout << "\n";

	DescribeObjects();
}

void Room::DescribeObjects() const {
	for (Entity* obj : GetInventory()) {
		cout << obj->GetDescription() << endl;
		Container* container = dynamic_cast<Container*>(obj);
		if (container && container->IsOpen()) {
			vector<Item*> items = container->GetInventory();
			if (!items.empty()) {
				cout << "The " << obj->GetName() << " contains:\n";
				for (Item* item : items) {
					cout << "A " << item->GetName() << endl;
				}
			}
		}
	}
}