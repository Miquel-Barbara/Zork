#ifndef __StatType__
#define __StatType__

using namespace std;
#include <string>

enum StatType {
    Durability,
    Strength,
    Defense,
    Evasion,
    Accuracy,
    Speed,
    Hp
};

StatType StringToStat(const string& input);

string StatToString(StatType dir);

#endif

