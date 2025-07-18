#ifndef __Direction__
#define __Direction__

using namespace std;

#include <string>

enum class Direction {
    North,
    South,
    East,
    West,
    Up,
    Down,
    Invalid
};

Direction StringToDirection(const string& input);

string DirectionToString(Direction dir);

#endif
