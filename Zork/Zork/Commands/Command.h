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

    Command(map<int, vector<string>> pattern, ExecuteFunc func): pattern(pattern), executeFunc(func) {}

    const map<int, vector<string>>& GetPattern() const { return pattern; }

    void Execute(Game& game, const vector<string>& args) const {
        executeFunc(game, args);
    }

private:
    map<int, vector<string>> pattern;
    ExecuteFunc executeFunc;
};

#endif