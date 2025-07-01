#include "Creature.h"

Creature::Creature(const string& name, const string& description, map<StatType, StatValue> stats) : Entity(name, description), stats(stats)  {}

void Creature::Move(Room* room) {
	if (room != nullptr) {
		currentRoom = room;
	}
}

Room* Creature::GetCurrentRoom() {
	return currentRoom;
}

bool Creature::Equip(Equipment* equip) {
	Armor* armorToEquip = dynamic_cast<Armor*>(equip);
	Weapon* weaponToEquip = dynamic_cast<Weapon*>(equip);

	if (armorToEquip) {
		ArmorPart slot = armorToEquip->GetArmorPart();
		auto it = equipment.find(slot);
		if (it != equipment.end()) {
			Unequip(it->second);
		}
		equipment[slot] = armorToEquip;
		RemoveItem(armorToEquip);
		return true;
	} else if (weaponToEquip) {
		if (weapon) {
			Unequip(weapon);
		}
		weapon = weaponToEquip;
		RemoveItem(weaponToEquip);
		return true;
	}
}

bool Creature::Unequip(Equipment* unequip) {
	Armor* armorToUnequip = dynamic_cast<Armor*>(unequip);
	Weapon* weaponToUnequip = dynamic_cast<Weapon*>(unequip);

	if (armorToUnequip) {
		ArmorPart slot = armorToUnequip->GetArmorPart();
		auto it = equipment.find(slot);
		if (it != equipment.end() && it->second == armorToUnequip) {
			equipment.erase(it);
			AddItem(armorToUnequip);
			return true;
		}
	} else if (weaponToUnequip) {
		if (weapon == weaponToUnequip) {
			weapon = nullptr;
			AddItem(weaponToUnequip);
			return true;
		}
	}
	return false;
}

vector<Equipment*> Creature::GetAllEquipment() const {
	vector<Equipment*> allEquipment;
	for (const auto& pair : equipment) {
		allEquipment.push_back(pair.second);
	}
	if (weapon) {
		allEquipment.push_back(weapon);
	}
	return allEquipment;
}

Weapon* Creature::GetEquippedWeapon() const {
	return weapon;
}

Equipment* Creature::GetEquippedArmor(ArmorPart slot) const {
	auto it = equipment.find(slot);
	if (it != equipment.end()) {
		return it->second;
	}
	return nullptr;
}

StatValue Creature::GetStat(StatType stat) const {
	auto it = stats.find(stat);
	if (it != stats.end()) {
		return it->second;
	}
	return 0;
}
