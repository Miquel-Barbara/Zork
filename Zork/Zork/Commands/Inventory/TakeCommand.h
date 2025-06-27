#ifndef __TakeCommand__
#define __TakeCommand__

using namespace std;

#include "../Command.h"

class TakeCommand : public Command {
public:
    bool Execute(Game& game, const vector<string>& args) override;
    map<int, string> GetPattern() const override;
};

#endif
