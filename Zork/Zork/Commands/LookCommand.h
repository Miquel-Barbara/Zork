#ifndef __LookCommand__
#define __LookCommand__

using namespace std;

#include "Command.h"

class LookCommand : public Command {
public:
    bool Execute(Game& game, const vector<string>& args) override;
    string GetName() const override { return "look"; }
};

#endif