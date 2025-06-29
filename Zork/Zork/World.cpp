#include <iostream>
#include "World.h"
#include "Room.h"
#include "Entity.h"
#include "Item.h"
#include "Exit.h"
#include "Container.h"
#include "RestrictedExit.h"

World::World() {
	//------------Rooms------------//
	Room* westHouse = new Room("West of House", "You are standing in an open field west of a white house, with a boarded front door.");
	Room* southHouse = new Room("South of House", "You are facing the south side of a white house. There is no door here, and all the windows are boarded.");
	Room* behindHouse = new Room("Behind of House", "You are behind the white house.");
	Room* kitchen = new Room("Kitchen", "You are in the kitchen of the white house.  A table seems to have been used recently for the preparation of food.  A passage leads to the west and a dark staircase can be seen leading upward.");
	
	//------------Exits------------//
	Exit* exit = new Exit(Direction::South, westHouse, southHouse);
	westHouse->AddExit(exit);
	RestrictedExit* door = new RestrictedExit(Direction::East, southHouse, kitchen, "", "", "The door cannot be opened.", "That's not something you can close.", "The door is locked, and there is evidently no key.", make_shared<bool>(false), false);
	westHouse->AddExit(door);

	Exit* exit2 = new Exit(Direction::West, southHouse, westHouse);
	southHouse->AddExit(exit2);
	Exit* exit3 = new Exit(Direction::East, southHouse, behindHouse);
	southHouse->AddExit(exit3);

	Exit* exit4 = new Exit(Direction::South, behindHouse, southHouse);
	behindHouse->AddExit(exit4);
	shared_ptr<bool> isOpenWindow = make_shared<bool>(false);
	RestrictedExit* exit5 = new RestrictedExit(Direction::West, behindHouse, kitchen, "In one corner of the house there is a small window which is open.", "In one corner of the house there is a small window which is slightly ajar.", "With great effort, you open the window far enough to allow entry.", "The window closes (more easily than it opened).", "The window is closed.", isOpenWindow);
	behindHouse->AddExit(exit5);

	RestrictedExit* exit6 = new RestrictedExit(Direction::East, kitchen, behindHouse, "To the east is a small window which is open.", "In one corner of the house there is a small window which is slightly ajar.", "With great effort, you open the window far enough to allow entry.", "The window closes (more easily than it opened).", "The window is closed.", isOpenWindow);
	kitchen->AddExit(exit6);

	//------------West House Entities------------//
	Item* leaflet = new Item("leaflet", "A leaflet with the text: 'Welcome to Zork!'");
	Container* mailbox = new Container("mailbox", "There is a small mailbox here.");
	mailbox->AddItem(leaflet);
	westHouse->AddItem(mailbox);

	Item* rubberMat = new Item("rubber mat", "A rubber mat saying 'Welcome to Zork!' lies by the door.");
	westHouse->AddItem(rubberMat);

	//Starting Room
	startRoom = westHouse;
}

Room* World::GetStartRoom() {
	return startRoom;
}