#ifndef __Enemy__
#define __Enemy__

#include "Creature.h"
#include "../Others/Stat.h"

class Enemy : public Creature {
public:
    Enemy(const string& name, const string& description, map<StatType, StatValue*> stats, vector<string> attackDescription, string deadDescription);
    void Tick();
    void Die();
private:
    string deadDescription;
    vector<string> attackDescription;
};

#endif
