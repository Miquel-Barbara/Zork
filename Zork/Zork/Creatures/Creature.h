#ifndef CREATURE_H  
#define CREATURE_H  

#include "../Entity.h"
#include "../Objects/Item.h"
#include "../Inventory.h"
#include "../World/Room.h"
#include <map>
#include "../Objects/Armor.h"
#include "../Enums/ArmorPart.h"
#include "../Objects/Weapon.h"

#include "../Others/Stat.h"
#include "../Enums/StatType.h"

class Room;

class Creature : public Entity, public Inventory<Item> {
public:
	Creature(const string& name, const string& description, map<StatType, StatValue*> stats);

	void Move(Room* room);
	Room* GetCurrentRoom();

	bool Equip(Equipment* equipment);
	bool Unequip(Equipment* equipment);

	Weapon* GetEquippedWeapon() const;
	Equipment* GetEquippedArmor(ArmorPart slot) const;
	vector<Equipment*> GetAllEquipment() const;

	int GetStat(StatType stat) const;
	vector<StatType> GetAllStats() const;

protected:
	Room* currentRoom; 

	Weapon* weapon;
	map<ArmorPart, Equipment*> equipment;

	map<StatType, StatValue*> stats;
};

#endif 