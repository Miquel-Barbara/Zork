#include "Creature.h"

Creature::Creature(const std::string& name, const std::string& description) 
	: Entity(name, description), currentRoom(nullptr) {}

void Creature::Move(Room* room) {
	if (room != nullptr) {
		currentRoom = room;
	}
}
