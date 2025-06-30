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
	void CreateAllRooms();
	void CreateAllConnections();
	void CreateAllItems();

private:
	Room* startRoom;

	//----Nearby House----//
	Room* westHouse;
	Room* northHouse;
	Room* southHouse;
	Room* behindHouse;

	//----Inside House----//
	Room* kitchen;
	Room* livingRoom;
	Room* attic;

	//----Forest----//
	Room* forest1;
	Room* forest2;

	//----Forest2----//
	Room* forestPath;
	Room* upATree;
	Room* clearing;

	//----Under House----//
	Room* trollRoom;
	Room* cellar;
	Room* gallery;
	Room* studio;

	Room* endRoom;
};

#endif
