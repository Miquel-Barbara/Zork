#ifndef __Npc__
#define __Npc__

#include "Creature.h"
#include "../Others/Stat.h"

class Npc : public Creature {
public:
    Npc(const string& name, const string& description, map<StatType, StatValue*> stats);

private:

};

#endif
