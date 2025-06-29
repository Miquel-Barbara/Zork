#ifndef __Armor__
#define __Armor__

#include "Objects/Equipment.h"
#include "ArmorPart.h"

class Armor : public Equipment {
public:
    Armor(const string& name, const string& description,
        int durability, int defense, int evasion, int extraHP, int velocity, ArmorPart armorPart);

    ArmorPart GetArmorPart() const;
    int GetDefense() const;
    int GetEvasion() const;
    int GetExtraHP() const;
    int GetVelocity() const;

private:
    ArmorPart armorPart;
};

#endif
