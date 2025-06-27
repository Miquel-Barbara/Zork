#ifndef __Game__
#define __Game__

using namespace std;

#include <map>
#include <string>
#include <vector>
#include "Room.h"
#include "Commands/Command.h"
#include "World.h"
#include "Item.h"

class Command;
class Room;
class World;

class Game {
public:
    Game();

    void RegisterCommand(Command* command);
    void ProcessInput(const string& input);

    Room* GetCurrentRoom() const;
    void SetCurrentRoom(Room* room);

    vector<Item*>& GetInventory() { return inventory; }

private:
    vector<Command*> commands;
    World* world;
    Room* currentRoom;
    vector<Item*> inventory;
};

#endif