#include "Direction.h"

Direction StringToDirection(const string& input) {
    if (input == "north") return Direction::North;
    if (input == "south") return Direction::South;
    if (input == "east")  return Direction::East;
    if (input == "west")  return Direction::West;
    if (input == "up")    return Direction::Up;
    if (input == "down")  return Direction::Down;
    return Direction::Invalid;
}

string DirectionToString(Direction dir) {
    switch (dir) {
    case Direction::North: return "north";
    case Direction::South: return "south";
    case Direction::East:  return "east";
    case Direction::West:  return "west";
    case Direction::Up:    return "up";
    case Direction::Down:  return "down";
    default: return "invalid";
    }
}