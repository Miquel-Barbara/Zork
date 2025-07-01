#ifndef __Equipment__
#define __Equipment__

#include "Item.h"
#include "../Others/Stat.h"
#include <map>
#include <string>

class Equipment : public Item {
public:
    Equipment(const string& name, const string& description, int durability);
    bool IsBroken() const;

protected:
    map<StatType, int> stats = {};
};

#endif
