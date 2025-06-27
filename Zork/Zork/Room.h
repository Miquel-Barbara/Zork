#ifndef __Room__
#define __Room__

using namespace std;

#include <string>
#include <map>
#include <memory>
#include "Direction.h"
#include <vector>
#include "Item.h"
#include <functional>
#include "Game.h"
#include "Entity.h"

class Game;

struct RoomAction {
	string verb;           
	string target;        
	function<void(Game&)> effect;
	function<bool(Game&)> precondition;
};

class Room : public Entity{
public:
	Room(const string& name, const string& description);

	void SetConnection(Direction direction, Room* room);
	Room* GetConnectedRoom(Direction direction);

private:
	map<Direction, Room*> connections;
};

#endif
