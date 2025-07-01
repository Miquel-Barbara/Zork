#include "StatType.h"

StatType StringToStat(const string& str) {
	if (str == "durability") return StatType::Durability;
	if (str == "accuracy") return StatType::Accuracy;
	if (str == "defense") return StatType::Defense;
	if (str == "speed") return StatType::Speed;
	if (str == "evasion") return StatType::Evasion;
	if (str == "Strength") return StatType::Strength;
	if (str == "Hp") return StatType::Hp;
}

string StatToString(StatType stat) {
	switch (stat) {
		case StatType::Durability: return "durability";
		case StatType::Accuracy: return "accuracy";
		case StatType::Defense: return "defense";
		case StatType::Speed: return "speed";
		case StatType::Evasion: return "evasion";
		case StatType::Strength: return "strength";
		case StatType::Hp: return "hp";
	}
}