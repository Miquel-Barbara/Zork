#ifndef __Equipment__
#define __Equipment__

#include "EquipmentSlot.h"
#include "Item.h"

class Equipment: public Item {
public:
    virtual ~Equipment() = default;

    virtual EquipmentSlot GetSlot() const = 0;
    virtual void Equip() = 0;
    virtual void Unequip() = 0;
    virtual bool IsEquipped() const = 0;

private:
    EquipmentSlot slot;
};

#endif
