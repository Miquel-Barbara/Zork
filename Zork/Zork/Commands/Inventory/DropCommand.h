#ifndef __DropCommand__
#define __DropCommand__

#include "../Command.h"

class DropCommand : public Command {
public:
    bool Execute(Game& game, const vector<string>& args) override;
    map<int, string> GetPattern() const override;
};

#endif
