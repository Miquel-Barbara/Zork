#ifndef __Room__
#define __Room__

using namespace std;

#include <string>
#include <map>
#include <memory>
#include "Direction.h"


class Room {
public:
	Room(const string& name, const string& description);

	void SetConnection(Direction direction, Room* room);
	Room* GetConnectedRoom(Direction direction);

	string GetName();
	string GetDescription();

private:
	string name;
	string description;
	map<Direction, Room*> connections;
};

#endif
