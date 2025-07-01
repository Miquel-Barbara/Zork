#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Creature.h"
#include "../Others/Stat.h"

class Player : public Creature {
public:
	Player(const string& name, const string& description, map<StatType, StatValue*> stats);
private:

};

#endif 
