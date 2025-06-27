#ifndef __Command__
#define __Command__

using namespace std;

#include <string>
#include <vector>
#include "../Game.h"

class Game;

class Command {
public:
    virtual ~Command() {}
    virtual bool Execute(Game& game, const vector<string>& args) = 0;
    virtual map<int, string> GetPattern() const = 0;
};

#endif