#include "CommandGenerator.h"

#include "../RestrictedExit.h"

#include "../Objects/Container.h"


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
                exit->MoveToDestination(game.GetPlayer());
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
                        game.GetPlayer()->AddItem(item);
                        current->RemoveItem(item);
                        break;
                    }
                }
            }

            if (!item) {
                for (Object* entity : entities) {
                    Container* container = dynamic_cast<Container*>(entity);
                    if (container && container->IsOpen()) {
                        vector<Item*> items = container->GetInventory();
                        for (Item* it : items) {
                            if (it->GetName() == itemName) {
                                item = it;
                                game.GetPlayer()->AddItem(item);
                                container->RemoveItem(item);
                                break;
                            }
                        }
                    }
                    if (item) break;
                }
            }

            if (item) {
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
                room->DescribeAll();
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
            //Check if we open a exit in the Room
            for (Exit* exit : exits) {
                RestrictedExit* restExit = dynamic_cast<RestrictedExit*>(exit);
                if (restExit && args[0] == restExit->GetName()) {
                    if (!restExit->IsOpen()) {
                        restExit->Open();
                    }
                    else {
                        cout << "You think it isn't?\n";
                    }
                }
			}

            //Check if we open a container in the Room
			vector<Object*> objects = current->GetInventory();
			for (Object* obj : objects) {
				Container* container = dynamic_cast<Container*>(obj);
				if (container && !container->IsOpen()  && args[0] == container->GetName()) {
					container->Open();

                    cout << "You open the " << container->GetName();
                    if (!container->GetInventory().empty()) {
                        cout << ", revealing a ";
                        for (size_t i = 0; i < container->GetInventory().size(); ++i) {
							cout << container->GetInventory()[i]->GetName();
							if (i < container->GetInventory().size() - 1) {
								cout << ", ";
							}
						}
                    }
				}
			}

            //Check if we open a container in the Inventory
            vector<Item*> inventory = game.GetPlayer()->GetInventory();
            for (Item* item : inventory) {
                Container* container = dynamic_cast<Container*>(item);
				if (container && !container->IsOpen() && args[0] == container->GetName()) {
					container->Open();
				}
			}

            cout << "\n";
		}
	);
}

Command* CreateCloseCommand() {
	return new Command(
		{ {0, {"close"}} },
		[](Game& game, const vector<string>& args) {
			Room* current = game.GetPlayer()->GetCurrentRoom();


			vector<Exit*> exits = current->GetExits();
            // Check if we close a exit in the Room
			for (Exit* exit : exits) {
                RestrictedExit* restExit = dynamic_cast<RestrictedExit*>(exit);
				if (restExit) {
					if (restExit->IsOpen()) {
                        restExit->Close();
					}
					else {
						cout << "I think you've already done that.\n";
					}
				}
			}

            // Check if we close a container in the Room
            vector<Object*> objects = current->GetInventory();
            for (Object* obj : objects) {
                Container* container = dynamic_cast<Container*>(obj);
                if (container && container->IsOpen()) {
					container->Close();

                    cout << "You close the " << container->GetName();
				}
            }

			// Check if we close a container in the Inventory
            vector<Item*> inventory = game.GetPlayer()->GetInventory();
            for (Item* item : inventory) {
                Container* container = dynamic_cast<Container*>(item);
                if (container && container->IsOpen()) {
                    container->Close();
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
