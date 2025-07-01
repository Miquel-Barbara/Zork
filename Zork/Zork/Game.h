#ifndef __Game__
#define __Game__

using namespace std;

#include <map>
#include <string>
#include <vector>
#include "World/Room.h"
#include "Commands/Command.h"
#include "Commands/CommandFactory.h"
#include "World/World.h"
#include "Objects/Item.h"
#include "Creatures/Player.h"

class World;
class CommandFactory;
class Player;


class Game {
public:
    Game();

    void ProcessInput(const string& input);
    Player* GetPlayer();
    void Quit() { quit = true; }
    bool EndGame() const;

private:
    World* world;
    Player* player;
    CommandFactory* commandFactory;
    bool quit;
};

#endif