#include "Room.h"

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