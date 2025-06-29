#include "Creature.h"

Creature::Creature(const string& name, const string& description) : Entity(name, description) {}

void Creature::Move(Room* room) {
	if (room != nullptr) {
		currentRoom = room;
	}
}

Room* Creature::GetCurrentRoom() {
	return currentRoom;
}
