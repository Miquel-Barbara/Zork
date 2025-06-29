#include "Exit.h"

Exit::Exit(const string& name, const string& description, Direction direction, Room* source, Room* destination)
	: direction(direction), sourceRoom(source), destinationRoom(destination), Entity(name, description) {}

void Exit::MoveToDestination(Creature* creature) const {
	if (destinationRoom) {
		creature->Move(destinationRoom);
		destinationRoom->DescribeAll();
	}
}