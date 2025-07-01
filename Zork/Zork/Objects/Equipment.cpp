#include "Equipment.h"

Equipment::Equipment(const string& name, const string& description, int durability)
	: Item(name, description), Object(name, description) {
	stats[StatType::Durability] = durability;
}

bool Equipment::IsBroken() const {
	return GetStat(StatType::Durability) <= 0;
}

int Equipment::GetStat(StatType statType) const {
	auto it = stats.find(statType);
	if (it != stats.end()) {
		return it->second;
	}
	return 0;
}
