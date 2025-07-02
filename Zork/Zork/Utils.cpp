#include "Utils.h"

void InitRandom() {
    srand(static_cast<unsigned int>(time(nullptr)));
}

bool Chance(int percentage) {
    if (percentage <= 0) return false;
    if (percentage >= 100) return true;
    int roll = rand() % 100; // 0 to 99
    return roll < percentage;
}

string toLower(const string& input) {
    string result = input;
    transform(result.begin(), result.end(), result.begin(),
        [](unsigned char c) { return tolower(c); });
    return result;
}

int RandomRange(int maxExclusive) {
    if (maxExclusive <= 0) return 0;
    return rand() % maxExclusive;
}

int RandomRange(int minInclusive, int maxInclusive) {
    if (maxInclusive < minInclusive) return minInclusive;
    return minInclusive + rand() % (maxInclusive - minInclusive + 1);
}