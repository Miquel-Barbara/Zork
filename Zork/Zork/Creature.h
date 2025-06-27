#ifndef __Creature__
#define __Creature__

#include "Entity.h"
#include "Room.h"

class Creature : public Entity {
public:
    Creature(const string& name, const string& description);
    void Move(Room* newRoom);
private:
    Room* currentRoom;  
};

#endif
