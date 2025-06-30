#ifndef CREATURE_H  
#define CREATURE_H  

#include "../Entity.h"
#include "../Objects/Item.h"
#include "../Inventory.h"
#include "../Room.h"
#include <map>
#include "../Armor.h"
#include "../ArmorPart.h"
#include "../Weapon.h"

#include "../Stat.h"
#include "../Stat.h"

class Room;

class Creature : public Entity, public Inventory<Item> {
public:
	Creature(const string& name, const string& description, map<StatType, StatValue> stats);

	void Move(Room* room);
	Room* GetCurrentRoom();

	bool Equip(Equipment* equipment);
	bool Unequip(Equipment* equipment);

	Weapon* GetEquippedWeapon() const;
	Equipment* GetEquippedArmor(ArmorPart slot) const;

	StatValue GetStat(StatType stat) const;

protected:
	Room* currentRoom; 

	Weapon* weapon;
	map<ArmorPart, Equipment*> equipment;

	map<StatType, StatValue> stats;
};

#endif 