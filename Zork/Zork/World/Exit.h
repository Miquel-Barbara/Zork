#ifndef __Exit__
#define __Exit__

using namespace std;

#include <string>
#include "../Entity.h"
#include "../Enums/Direction.h"
#include "Room.h"
#include "../Creatures/Creature.h"

class Game;
class Creature;
class Room;

class Exit: public Entity {
public:
	Exit(const string& name, const string& description, Direction direction, Room* source, Room* destination);
	virtual void MoveToDestination(Creature* creature) const;
	Direction GetDirection() const { return direction; }
	Room* GetSourceRoom() const { return sourceRoom; }
	Room* GetDestinationRoom() const { return destinationRoom; }

private:
	Direction direction;
	Room* sourceRoom;
	Room* destinationRoom;
};

#endif
