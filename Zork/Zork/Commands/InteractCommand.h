#ifndef __InteractCommand__
#define __InteractCommand__

#include "Command.h"

class InteractCommand : public Command {
public:
    bool Execute(Game& game, const std::vector<std::string>& args) override;
    map<int, string> GetPattern() const override;
};

#endif
