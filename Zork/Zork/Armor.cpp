#include "Armor.h"

Armor::Armor(const string& name, const string& description, int durability, int defense, int evasion, int extraHP, int velocity, ArmorPart armorPart)
	: Equipment(name, description, durability), armorPart(armorPart) {
	stats[StatType::Defense] = defense;
	stats[StatType::Evasion] = evasion;
	stats[StatType::Hp] = extraHP;
	stats[StatType::Speed] = velocity;
}

ArmorPart Armor::GetArmorPart() const {
	return armorPart;
}