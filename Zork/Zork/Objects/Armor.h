#ifndef __Armor__
#define __Armor__

#include "Equipment.h"
#include "../Enums/ArmorPart.h"
#include <map>

using namespace std;

class Armor : public Equipment {
public:
    Armor(const string& name, const string& description,
        int durability, int defense, int evasion, int extraHP, int velocity, ArmorPart armorPart);

    ArmorPart GetArmorPart() const;

private:
    ArmorPart armorPart;
};

#endif
