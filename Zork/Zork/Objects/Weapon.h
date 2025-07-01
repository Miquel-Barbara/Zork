#ifndef __Weapon__
#define __Weapon__

#include "Equipment.h"
#include "../Others/Stat.h"

class Weapon : public Equipment {
public:
    Weapon(const string& name, const string& description,int durability, int attackPower, int accuracy);
private:
};

#endif
