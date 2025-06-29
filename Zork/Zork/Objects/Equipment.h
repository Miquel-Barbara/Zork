#ifndef __Equipment__
#define __Equipment__

#include "Item.h"
#include "../Stat.h"

class Equipment : public Item {
public:
    Equipment(const string& name, const string& description, int durability);

    int GetDurability() const;
    void ReduceDurability(int amount);
    bool IsBroken() const;

protected:
    map<StatType, int> stats;
};

#endif
