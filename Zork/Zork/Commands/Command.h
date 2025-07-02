#ifndef __Command__
#define __Command__

using namespace std;

#include <iostream>
#include <functional>
#include <string>
#include <map>
#include <vector>
#include "../Game.h"

using namespace std;

class Game;

class Command {
public:
    using ExecuteFunc = function<void(Game& ,const vector<string>&)>;

    Command(map<int, vector<string>> pattern, ExecuteFunc func, bool itTicks = true): pattern(pattern), executeFunc(func), itTicks(itTicks) {}

    const map<int, vector<string>>& GetPattern() const { return pattern; }

    void Execute(Game& game, const vector<string>& args) const {
        executeFunc(game, args);
    }

    bool ItTicks() const { return itTicks; }

private:
    map<int, vector<string>> pattern;
    ExecuteFunc executeFunc;
    bool itTicks;
};

#endif