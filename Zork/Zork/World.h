#ifndef __World__
#define __World__

#include <string>
#include <list>
#include <time.h>
#include "Room.h"

class Room;

class World {
public:
	World();
	Room* GetStartRoom();

private:
	Room* startRoom;
};

#endif
