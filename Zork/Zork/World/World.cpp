#include <iostream>
#include "World.h"
#include "Room.h"
#include "../Entity.h"
#include "../Objects/Item.h"
#include "Exit.h"
#include "../Objects/Container.h"
#include "../Objects/ItemContainer.h"
#include "../Objects/Weapon.h"
#include "../Objects/Armor.h"
#include "RestrictedExit.h"
#include "../Enums/Direction.h"

World::World() {	
	CreateAllRooms();
	CreateAllConnections();
	CreateAllItems();
	//Starting Room
	startRoom = westHouse;
}

Room* World::GetStartRoom() {
	return startRoom;
}

void World::CreateAllRooms() {
	//----Nearby House----//
	westHouse = new Room("West of House", "You are standing in an open field west of a white house, with a boarded front door.");
	southHouse = new Room("South of House", "You are facing the south side of a white house. There is no door here, and all the windows are boarded.");
	behindHouse = new Room("Behind of House", "You are behind the white house.");
	northHouse = new Room("North of House", "You are facing the north side of a white house.  There is no door here, and all the windows are barred.");

	//----Inside House----//
	kitchen = new Room("Kitchen", "You are in the kitchen of the white house.  A table seems to have been used recently for the preparation of food.  A passage leads to the west and a dark staircase can be seen leading upward.");
	livingRoom = new Room("Living Room", "You are in the living room. There is a doorway to the east, a wooden door with strange gothic lettering to the west, which appears to be nailed shut, a trophy case, and a large oriental rug in the center of the room. Above the trophy case hangs an elvish sword of great antiquity. A battery - powered brass lantern is on the trophy case.");
	attic = new Room("Attic", "This is the attic. The only exit is a stairway leading down.");
	
	//----Forest----//
	forest1 = new Room("Forest", "This is a forest, with trees in all directions around you.");
	forest2 = new Room("Forest", "This is a dimly lit forest, with large trees all around.  To the east, there appears to be sunlight.");
	
	//----Forest2----//
	forestPath = new Room("Forest", "This is a dimly lit forest, with large trees all around.  One particularly large tree with some low branches stands here. There is a corpse near the tree where the upper half of the body is missing, despite all it is still wearing pants and boots");
	upATree = new Room("Up a Tree",  "You are about 10 feet above the ground nestled among some large branches.  The nearest branch above you is above your reach.On the branch is a small birds nest. In the bird's nest is a large egg encrusted with precious jewels, apparently scavenged somewhere by a childless songbird.  The egg is covered with fine gold inlay, and ornamented in lapis lazuli and mother-of-pearl.  Unlike most eggs, this one is hinged and has a delicate looking clasp holding it closed.  The egg appears extremely fragile.");
	clearing = new Room("Clearing", "You are in a clearing, with a forest surrounding you on the west and south. There is a pile of leaves on the ground.");

	//----Under House----//
	studio = new Room("Studio", "This appears to have been an artist's studio. The walls and floors are splattered with paints of 69 different colors. Strangely enough, nothing of value is hanging here. At the south end of the room is an open door (also covered with paint). A dark and narrow chimney leads up from a fireplace; although you might be able to get up it, it seems unlikely you could get back down.Loosely attached to a wall is a small piece of paper.");
	cellar = new Room("Cellar", "You are in a dark and damp cellar with a narrow passageway leading north, and a crawlway to the south. On the west is the bottom of a steep metal ramp which is unclimbable.");
	gallery = new Room("Gallery", "This is an art gallery. Most of the paintings have been stolen by vandals with exceptional taste. The vandals left through either the north or west exits.Fortunately, there is still one chance for you to be a vandal, for on the far wall is a painting of unparalleled beauty.");
	trollRoom = new Room("Troll Room", "This is a small room with passages to the east and south and a forbidding hole leading west. Bloodstains and deep scratches (perhaps made by an axe) mar the walls. A nasty - looking troll, brandishing a bloody axe, blocks all passages out of the room. Your sword has begun to glow very brightly. The troll's mighty blow drops you to your knees.");

	endRoom = new Room("The Void", "There is nothing here, except for a leaflet.");
}

void World::CreateAllConnections() {
	//----West House----//
	westHouse->AddExit(new Exit("", "", Direction::South, westHouse, southHouse));
	westHouse->AddExit(new Exit("", "", Direction::West, westHouse, forest1));
	westHouse->AddExit(new RestrictedExit("door", "", Direction::East, southHouse, kitchen, "", "", "The door cannot be opened.", "That's not something you can close.", "The door is locked, and there is evidently no key.", make_shared<bool>(false), false));
	westHouse->AddExit(new Exit("", "", Direction::North, westHouse, northHouse));

	//----South House----//
	southHouse->AddExit(new Exit("", "", Direction::West, southHouse, westHouse));
	southHouse->AddExit(new Exit("", "", Direction::East, southHouse, behindHouse));
	southHouse->AddExit(new Exit("", "", Direction::South, southHouse, forest2));

	//----Behind House----//
	behindHouse->AddExit(new Exit("", "", Direction::South, behindHouse, southHouse));
	behindHouse->AddExit(new Exit("", "", Direction::East, behindHouse, clearing));
	shared_ptr<bool> isOpenWindow = make_shared<bool>(false);
	behindHouse->AddExit(new RestrictedExit("window", "", Direction::West, behindHouse, kitchen, "In one corner of the house there is a small window which is open.", "In one corner of the house there is a small window which is slightly ajar.", "With great effort, you open the window far enough to allow entry.", "The window closes (more easily than it opened).", "The window is closed.", isOpenWindow));
	behindHouse->AddExit(new Exit("", "", Direction::West, behindHouse, northHouse));
	
	//----North House----//
	northHouse->AddExit(new Exit("", "", Direction::East, northHouse, behindHouse));
	northHouse->AddExit(new Exit("", "", Direction::West, northHouse, westHouse));

	//----Kitchen House----//
	kitchen->AddExit(new RestrictedExit("window", "", Direction::East, kitchen, behindHouse, "To the east is a small window which is open.", "In one corner of the house there is a small window which is slightly ajar.", "With great effort, you open the window far enough to allow entry.", "The window closes (more easily than it opened).", "The window is closed.", isOpenWindow));
	kitchen->AddExit(new Exit("", "", Direction::Up, kitchen, attic));
	kitchen->AddExit(new Exit("", "", Direction::West, kitchen, livingRoom));

	//----Attic House----//
	attic->AddExit(new Exit("", "", Direction::Down, attic, kitchen));

	//----Living Room House----//
	livingRoom->AddExit(new Exit("", "", Direction::East, livingRoom, kitchen));
	livingRoom->AddExit(new Exit("", "", Direction::Down, livingRoom, cellar));

	//----Forest----//
	forest1->AddExit(new Exit("", "", Direction::West, forest1, westHouse));
	forest1->AddExit(new Exit("", "", Direction::East, forest1, forestPath));
	forest1->AddExit(new Exit("", "", Direction::South, forest1, forest2));
	forest1->AddExit(new Exit("", "", Direction::North, forest1, clearing));

	forest2->AddExit(new Exit("", "", Direction::North, forest2, forest1));
	forest2->AddExit(new Exit("", "", Direction::East, forest2, clearing));
	forest2->AddExit(new Exit("", "", Direction::West, forest2, southHouse));
	forest2->AddExit(new Exit("", "", Direction::West, forest2, forestPath));

	clearing->AddExit(new Exit("", "", Direction::West, clearing, forest1));
	clearing->AddExit(new Exit("", "", Direction::South, clearing, forest2));

	forestPath->AddExit(new Exit("", "", Direction::East, forestPath, clearing));
	forestPath->AddExit(new Exit("", "", Direction::West, forestPath, northHouse));
	forestPath->AddExit(new Exit("", "", Direction::South, forestPath, forest1));
	forestPath->AddExit(new Exit("", "", Direction::North, forestPath, forest2));
	forestPath->AddExit(new Exit("", "", Direction::Up, forestPath, upATree));

	upATree->AddExit(new Exit("", "", Direction::Down, upATree, forestPath));

	//----Cellar----//
	cellar->AddExit(new Exit("", "", Direction::North, cellar, trollRoom));
	cellar->AddExit(new Exit("", "", Direction::South, cellar, gallery));
	cellar->AddExit(new Exit("", "", Direction::Up, cellar, livingRoom));

	//----Gallery----//
	gallery->AddExit(new Exit("", "", Direction::West, gallery, cellar));
	gallery->AddExit(new Exit("", "", Direction::North, gallery, studio));

	//----Studio----//
	studio->AddExit(new Exit("", "", Direction::South, studio, gallery));
}

void World::CreateAllItems() {
	//------------West House------------//
	Item* leaflet = new Item("leaflet", "A leaflet wrote with blood says: PUT THIS LEAFLET INSIDE THIS MAILBOX WAS A PAIN THAT I DIDN'T EXPECTED. You know, when you work with a mentality of OOP you struge sometimes in searching for the fititng solution, see, if the bottle of water that is in the kitchen could not be inside the mailbox it should be more easy but there is this problem that you can pickup a bottle that is a container but you can't pickup the mailbox that is also a container so how I do this?... well well great question that we have here and i can fit in this leaflet");
	Container* mailbox = new Container("mailbox", "There is a small mailbox here.", { leaflet });
	westHouse->AddItem(mailbox);

	Item* rubberMat = new Item("rubber mat", "A rubber mat saying 'Welcome to Zork!' lies by the door.");
	westHouse->AddItem(rubberMat);

	//------------North House------------//
	Armor* chest = new Armor("coat", "A coat lying on the ground appears to be in poor condition.", 20, 10, 5, 30, 0, ArmorPart::Chest);
	northHouse->AddItem(chest);


	//------------Kitchen------------//
	ItemContainer* bottle = new ItemContainer("bottle water", "A bottle is sitting on the table.", { new Item("water", "A bottle of water.") });
	kitchen->AddItem(bottle);
	ItemContainer* brownSack = new ItemContainer("brown sack", "On the table is an elongated brown sack, smelling of hot peppers.", {new Item("lunch", "I am so hungry..."), new Item("garlic", "Eww")});
	kitchen->AddItem(brownSack);
	
	//------------Living------------//
	Container* trophyCase = new Container("trophy case", "A trophy case is in the corner of the room.", {});
	livingRoom->AddItem(trophyCase);
	Item* lantern = new Item("lantern", "A battery-powered brass lantern is on the trophy case.");
	livingRoom->AddItem(lantern);
	Weapon* sword = new Weapon("sword", "A beautiful elvish sword of great antiquity hangs above the trophy case.", 100, 13, 90);
	livingRoom->AddItem(sword);
	Item* news = new Item("news", "There is an issue of DEVELOPER NOTES dated 30/06/25 here.");

	//------------Attic------------//
	Item* brick = new Item("square brick", "There is a square brick here which feels like clay.");
	attic->AddItem(brick);
	Item* rope = new Item("rope", "A large coil of rope is lying in the corner.");
	attic->AddItem(rope);
	Weapon* knife = new Weapon("knife", "A large kitchen knife is lying on the floor.", 50, 5, 70);
	attic->AddItem(knife);

	//------------Forest Path------------//
	Armor* boots = new Armor("boots", "", 50, 10, 10, 0, 20, ArmorPart::Feet);
	forestPath->AddItem(boots);
	Armor* legs = new Armor("pants", "", 60, 30, 0, 10, 0, ArmorPart::Legs);
	forestPath->AddItem(legs);

	//------------Gallery------------//
	Armor* arms = new Armor("gloves", "Gloves full of paint. Surely the bandits didn't find any value in them", 50, 10, 10, 0, 20, ArmorPart::Feet);
	gallery->AddItem(arms);

	Armor* chest2 = new Armor("armor", "A dented armor on the right side, it's as if a large object had hit it. With a little effort it will fit.", 40, 50, 10, 60, 0, ArmorPart::Feet);
	cellar->AddItem(chest2);
}