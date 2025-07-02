#ifndef __Utils__
#define __Utils__

using namespace std;

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cctype>
#include <string>

void InitRandom();

bool Chance(int percentage);

int RandomRange(int maxExclusive);

int RandomRange(int minInclusive, int maxInclusive);

string toLower(const string& input);

#endif
