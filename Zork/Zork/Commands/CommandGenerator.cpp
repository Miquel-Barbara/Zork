#include "CommandGenerator.h"

#include "../RestrictedExit.h"


Command* CreateMoveCommand() {
    return new Command(
        { {0, {"go"}} },
        [](Game& game, const vector<string>& args) {
            if (args.size() < 1) {
				cout << "You'll have to say which compass direction to go in.\n";
				return;return;
            }
                
            Direction dir = StringToDirection(args[0]);
            Room* current = game.GetPlayer()->GetCurrentRoom();
            Exit* exit = current->GetExit(dir);

            if (exit && exit->GetDirection() == dir) {
                // If the exit is a RestrictedExit, check if it's open
                game.GetPlayer()->Move(exit->GetDestinationRoom());
                return;

            }
            cout << "You can't go that way.\n";
        }
    );
}

Command* CreateTakeCommand() {
    return new Command(
        { {0, {"take", "get", "grab"}} },
        [](Game& game, const vector<string>& args) {
            string itemName = args[0];
            Room* current = game.GetPlayer()->GetCurrentRoom();
            vector<Object*> entities = current->GetInventory();

            Item* item = nullptr;
            for (Object* entity : entities) {
                if (entity->GetName() == itemName) {
                    item = dynamic_cast<Item*>(entity);
                    if (item) {
                        break;
                    }
                }
            }

            if (item) {
                game.GetPlayer()->AddItem(item);
                current->RemoveItem(item);
                cout << "Taken.\n" << endl;
            }
            else {
                cout << "You can't see any such thing.\n" << endl;
            }
        }
    );
}

Command* CreateDropCommand() {
    return new Command(
        { {0, {"drop"}} },
        [](Game& game, const vector<string>& args) {
            vector<Item*> inventory = game.GetPlayer()->GetInventory();
            string target = args[0];

            if (target == "all") {
                if (inventory.empty()) {
                    cout << "What do you want to drop those things in?\n";
                }

                Room* current = game.GetPlayer()->GetCurrentRoom();
                for (Item* item : inventory) {
                    inventory.erase(remove(inventory.begin(), inventory.end(), item), inventory.end());
                    current->AddItem(item);
                    cout << item->GetName() + " : Dropped";
                }

                cout << "You drop everything.\n";
                inventory.clear();
            }
            else {
                for (auto it = inventory.begin(); it != inventory.end(); ++it) {
                    if ((*it)->GetName() == target) {
                        Item* item = *it;
                        inventory.erase(it);
                        game.GetPlayer()->AddItem(item);
                        cout << "Dropped.\n";
                    }
                }

                cout << "You can't see any such thing.\n";
            }
            return;
        }
    );
}

Command* CreateInventoryCommand() {
    return new Command(
        { {0, {"inventory"}} },
        [](Game& game, const vector<string>& args) {
            vector<Item*> inventory = game.GetPlayer()->GetInventory();

            if (inventory.empty()) {
                cout << "You are empty handed." << endl;
            }
            else {
                cout << "You are carrying:" << endl;
                for (Item* item : inventory) {
                    cout << "- " << item->GetName() << endl;
                }
            }
        }
    );
}

Command* CreateLookCommand() {
    return new Command(
        { {0,  {"look"}} },
        [](Game& game, const vector<string>& args) {
            Room* room = game.GetPlayer()->GetCurrentRoom();

            if (room) {
                cout << room->GetName() << "\n";
                cout << room->GetDescription() << "\n";

                // Description of RestrictedExits
                for (Exit* exit : room->GetExits()) {
                    RestrictedExit* restExit = dynamic_cast<RestrictedExit*>(exit);
                    if (restExit) {
                        cout << restExit->GetDescription() << endl;
                    }
                }

                for (Object* obj : room->GetInventory()) {
                    Item* item = dynamic_cast<Item*>(obj);
                    if (item) {
                        cout << item->GetDescription() << endl;
                    }
                }
            }
            else {
                cout << "You are out of the boundaries of the map. Congrats!\n";
            }
            return;
        }
    );
}

Command* CreateDisplayCommand(vector<string> keyword, string message) {
	return new Command(
        { {0, keyword} },
		[message](Game& game, const vector<string>& args) {
			cout << message << endl;
		}
	);
}

Command* CreateDisplayCommand(string keyword, string message) {
    return new Command(
        { {0, {keyword}} },
        [message](Game& game, const vector<string>& args) {
            cout << message << endl;
        }
    );
}


Command* CreateOpenCommand() {
	return new Command(
		{ {0, {"open"}} },
		[](Game& game, const vector<string>& args) {
			Room* current = game.GetPlayer()->GetCurrentRoom();
            vector<Exit*> exits = current->GetExits();
            if (exits.empty()) {
                cout << "There is nothing to open here.\n";
				return;
			}
            for (Exit* exit : exits) {
				//Check if the entity is an Exit
                RestrictedExit* restExit = dynamic_cast<RestrictedExit*>(exit);
                if (restExit) {
                    if (restExit->IsOpen() == false) {
                        restExit->Open();
                    }
                    else {
                        cout << "You think it isn't?\n";
                    }
                }
			}
		}
	);
}

Command* CreateCloseCommand() {
	return new Command(
		{ {0, {"close"}} },
		[](Game& game, const vector<string>& args) {
			Room* current = game.GetPlayer()->GetCurrentRoom();
			vector<Exit*> exits = current->GetExits();
			if (exits.empty()) {
				cout << "There is nothing to close here.\n";
				return;
			}
			for (Exit* exit : exits) {
                RestrictedExit* restExit = dynamic_cast<RestrictedExit*>(exit);
				if (restExit) {
					if (restExit->IsOpen() == true) {
                        restExit->Close();
					}
					else {
						cout << "I think you've already done that.\n";
					}
				}
			}
		}
	);
}






vector<Command*> GenerateAllCommands() {
    return {
        CreateLookCommand(),
        CreateMoveCommand(),
        CreateTakeCommand(),
        CreateDropCommand(),
        CreateInventoryCommand(),
        CreateOpenCommand(),
        CreateCloseCommand(),
        CreateDisplayCommand("help", "Available commands: look, go, take, drop, inventory, help"),
        CreateDisplayCommand("bar", "Bar bar"),
        CreateDisplayCommand("Zork", "At your service"),
        CreateDisplayCommand("jump", "Are you proud of yourself?"),
        CreateDisplayCommand({"shout", "yell" , "scream"}, "Aaaarrrrgggghhhh!"),
        CreateDisplayCommand("hello", "Hello"),
    };
}
