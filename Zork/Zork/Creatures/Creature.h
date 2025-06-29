#ifndef CREATURE_H  
#define CREATURE_H  

#include "../Entity.h"
#include "../Item.h"
#include "../Inventory.h"
#include "../Room.h"

class Room;

class Creature : public Entity, public Inventory<Item> {
public:
	Creature(const string& name, const string& description);
	void Move(Room* room);

	Room* GetCurrentRoom();

protected:
	Room* currentRoom; 
};

#endif 