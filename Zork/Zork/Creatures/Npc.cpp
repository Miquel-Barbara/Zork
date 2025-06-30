#include "Npc.h"

Npc::Npc(const string& name, const string& description, map<StatType, StatValue> stats) : Creature(name, description, stats) {}