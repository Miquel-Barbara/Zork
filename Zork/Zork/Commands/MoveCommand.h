#ifndef __MoveCommand__
#define __MoveCommand__

using namespace std;

#include "Command.h"

class MoveCommand : public Command {
public:
    bool Execute(Game& game, const vector<string>& args) override;
    map<int, string> GetPattern() const override;
};

#endif