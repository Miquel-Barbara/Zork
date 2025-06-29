#include "Exit.h"

Exit::Exit(Direction direction, Room* source, Room* destination)
	: direction(direction), sourceRoom(source), destinationRoom(destination) {}

void Exit::MoveToDestination(Creature* creature) const {
	if (destinationRoom) {
		creature->Move(destinationRoom);
	}
}