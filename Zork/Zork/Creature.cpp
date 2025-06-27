#include "Creature.h"

Creature::Creature(const string& name, const string& description) : Entity(name, description) {}

void Creature::Move(Room* newRoom) {
	currentRoom = newRoom;
}