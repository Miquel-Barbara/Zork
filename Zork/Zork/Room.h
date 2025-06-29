#ifndef __Room__
#define __Room__

using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include "Entity.h"
#include "Inventory.h"
#include "Exit.h"
#include "Direction.h"

class Game;
class Exit;

class Room : public Entity, public Inventory<Object> {
public:
	Room(const string& name, const string& description);
	void DescribeAll() const;
	void DescribeObjects() const;

	void AddExit(Exit* exit);
	void RemoveExit(Exit* exit);

	Exit* GetExit(Direction direction) const;

	vector<Exit*> GetExits() const;

private:
	vector<Exit*> exits;
};

#endif
