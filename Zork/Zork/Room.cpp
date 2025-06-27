#include <iostream>
#include "Room.h"

Room::Room(const string& name, const string& description): Entity(name, description) {
	//cout << "Created room "+name+"." << endl;
}

void Room::SetConnection(Direction direction, Room* room) {
	//cout << "Added room connection  " + room->GetName() + " with direction: " + DirectionToString(direction) << endl;
	connections[direction] = room;
}

Room* Room::GetConnectedRoom(Direction direction) {
	auto it = connections.find(direction);
	if (it != connections.end()) {
		return it->second;
	}
	return nullptr;
}