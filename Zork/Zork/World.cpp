#include <iostream>
#include "World.h"
#include "Room.h"
#include "Entity.h"
#include "Item.h"

World::World() {
	//Create rooms
	Room* westHouse = new Room("West of House", "You are standing in an open field west of a white house, with a boarded front door.");
	Room* southHouse = new Room("South of House", "You are facing the south side of a white house. There is no door here, and all the windows are boarded.");
	Room* behindHouse = new Room("Behind of House", "You are behind the white house. A path leads into the forest to the east. In one corner of the house there is a small window which is slightly ajar.");
	Room* kitchen = new Room("Kitchen", "You are in the kitchen of the white house.A table seems to have been used recently for the preparation of food.A passage leads to the west and a dark staircase can be seen leading upward.A dark chimney leads down and to the east is a small window which is open. \nOn the table is an elongated brown sack, smelling of hot peppers.\nA bottle is sitting on the table.\nThe glass bottle contains :\nA quantity of water");

	//Set connections
	westHouse->SetConnection(Direction::South, southHouse);
	southHouse->SetConnection(Direction::West, westHouse);
	southHouse->SetConnection(Direction::East, behindHouse);

	//Entities West of the House
	Entity* mailbox = new Entity("mailbox", "There is a small mailbox here.");
	Item* rubberMat = new Item("rubber mat", "A rubber mat saying 'Welcome to Zork!' lies by the door.");
	Item* leaflet = new Item("leaflet", "A leaflet with the text: 'Welcome to Zork!'");

	mailbox->AddEntity(leaflet);
	westHouse->AddEntity(mailbox);
	westHouse->AddEntity(rubberMat);

	startRoom = westHouse;
}

Room* World::GetStartRoom() {
	return startRoom;
}