#ifndef CREATURE_H  
#define CREATURE_H  

#include "../Entity.h"
#include "../Objects/Item.h"
#include "../Inventory.h"
#include "../Room.h"
#include <map>
#include "../Armor.h"
#include "../Weapon.h"

#include "../Stat.h"

class Room;

class Creature : public Entity, public Inventory<Item> {
public:
	Creature(const string& name, const string& description);
	void Move(Room* room);
	Room* GetCurrentRoom();

	bool EquipWeapon(Weapon* weapon);
	bool EquipArmor(ArmorPart slot, Armor* armor);

	bool UnequipWeapon();
	bool UnequipArmor(ArmorPart slot);

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