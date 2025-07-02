#include "Creature.h"
#include "../Utils.h"

Creature::Creature(const string& name, const string& description, map<StatType, StatValue*> stats) : Entity(name, description), stats(stats)  {}

void Creature::Move(Room* room) {
	if (currentRoom) {
		currentRoom->RemoveItem(this);
	}
	if (room != nullptr) {
		currentRoom = room;
		currentRoom->AddItem(this);
	}
}

Room* Creature::GetCurrentRoom() {
	return currentRoom;
}

void Creature::Attack(Creature* creature) {
	if (Chance(GetStat(Accuracy) - creature->GetStat(Evasion))) {
		int damage = GetStat(Strength);
		cout << GetName() + " hits and deals " << to_string(damage) + " damage to " << creature->GetName() + "." << endl;
		creature->ReceiveDamage(damage);
	}
	else {
		cout << GetName() + " attacks but " << creature->GetName() +" dodge it!" << endl;
	}

	
}

void Creature::ReceiveDamage(int amount)
{
	stats[StatType::Hp]->Decrease(amount);
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

int Creature::GetStat(StatType stat) const {
	auto it = stats.find(stat);
	int equipmentValue = 0;

	for (Equipment* equipment : GetAllEquipment()) {
		if (equipment) {
			equipmentValue += equipment->GetStat(stat);
		}
	}

	if (it != stats.end()) {
		return it->second->Get() + equipmentValue;
	}
	return 0;
}

vector<StatType> Creature::GetAllStats() const {
	vector<StatType> statTypes;
	for (const auto& pair : stats) {
		statTypes.push_back(pair.first);
	}
	return statTypes;
}

bool Creature::IsDead() {
	int hp = GetStat(StatType::Hp);
	if (hp <= 0) {
		return true;
	} 
	return false;
}
