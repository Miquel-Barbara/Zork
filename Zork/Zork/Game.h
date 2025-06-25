#ifndef __Game__
#define __Game__

using namespace std;

#include <map>
#include <string>
#include <vector>
#include "Room.h"
#include "Commands/Command.h"
#include "World.h"

class Command;

class Game {
public:
    Game();

    void RegisterCommand(Command* command);
    void ProcessInput(const string& input);

    Room* GetCurrentRoom() const;
    void SetCurrentRoom(Room* room);

private:
    map<string, Command*> commands;
    World* world;
    Room* currentRoom;
};

#endif