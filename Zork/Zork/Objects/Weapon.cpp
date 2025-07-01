#include "Weapon.h"

Weapon::Weapon(const string& name, const string& description, int durability, int attackPower, int accuracy)
	: Equipment(name, description, durability), Object(name, description) {
	stats[StatType::Strength] = attackPower;
	stats[StatType::Accuracy] = accuracy;
}