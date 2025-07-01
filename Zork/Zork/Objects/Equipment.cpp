#include "Equipment.h"

Equipment::Equipment(const string& name, const string& description, int durability)
	: Item(name, description), Object(name, description) {
	stats[StatType::Durability] = durability;
}