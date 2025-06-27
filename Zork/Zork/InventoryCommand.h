#ifndef __InventoryCommand__
#define __InventoryCommand__

using namespace std;

#include "../Command.h"

class InventoryCommand : public Command {
public:
    bool Execute(Game& game, const vector<string>& args) override;
    string GetName() const override { return "inventory"; }
};

#endif
