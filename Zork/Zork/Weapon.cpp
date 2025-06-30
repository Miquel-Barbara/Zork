#include "Weapon.h"

Weapon::Weapon(const string& name, const string& description, int durability, int attackPower, int accuracy)
	: Equipment(name, description, durability) {
	stats[StatType::AttackPower] = attackPower;
	stats[StatType::Accuracy] = accuracy;
}