#include "CommandGenerator.h"
#include "../RestrictedExit.h"
#include "../Objects/Container.h"

namespace {
    template<typename T, typename Y>
    Y* FindInList(vector<T*> list, string name) {
        for (T* item : list) {
            Y* castedItem = dynamic_cast<Y*>(item);
            if (castedItem && castedItem->GetName() == name) {
                return castedItem;
            }
        }
        return nullptr;
    }
}

Command* CreateMoveCommand() {
    return new Command(
        { {0, {"go"}} },
        [](Game& game, const vector<string>& args) {
  
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

            Item* item = FindInList<Object, Item>(entities, itemName);
            if (item) {
				game.GetPlayer()->AddItem(item);
				current->RemoveItem(item);
				return;
            }
            else {
                Container* container = FindInList<Object, Container>(entities, itemName);
                if (container && container->IsOpen()) {
                    Item* item = FindInList<Item, Item>(container->GetInventory(), itemName);
                    if (item) {
                        game.GetPlayer()->AddItem(item);
                        container->RemoveItem(item);
                    }
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

Command* CreateOpenCommand() {
	return new Command(
		{ {0, {"open"}} },
		[](Game& game, const vector<string>& args) {
			Room* current = game.GetPlayer()->GetCurrentRoom();

            RestrictedExit* restExit = FindInList<Exit, RestrictedExit>(current->GetExits(), args[0]);
            if (restExit && !restExit->IsOpen()) {
                restExit->Open();
			}

            Container* container = FindInList<Object, Container>(current->GetInventory(), args[0]);
            if (container && !container->IsOpen()) {
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

            Container* inventoryContainer = FindInList<Item, Container>(game.GetPlayer()->GetInventory(), args[0]);
            if (container && !container->IsOpen()) {
                container->Open();
            }

            cout << "\n";
		}
	);
}

Command* CreateEquipCommand() {
    return new Command(
        { {0, {"equip"}} },
        [](Game& game, const vector<string>& args) {
            Equipment* itemToEquip = FindInList<Item, Equipment>(game.GetPlayer()->GetInventory(), args[0]);

            if (itemToEquip) {
                game.GetPlayer()->Equip(itemToEquip);
                cout << "You equip the " << itemToEquip->GetName() << ".\n";
            }
            else {
                cout << "You don't have that item in your inventory.\n";
            }
        }
    );
}

Command* CreateUnequipCommand() {
    return new Command(
        { {0, {"unequip"}} },
        [](Game& game, const vector<string>& args) {
            Equipment* itemToUnequip = FindInList<Item, Equipment>(game.GetPlayer()->GetInventory(), args[0]);

            if (itemToUnequip) {
                game.GetPlayer()->Unequip(itemToUnequip);
                cout << "You unequip the " << itemToUnequip->GetName() << ".\n";
            }
            else {
                cout << "You don't have that item in your inventory.\n";
            }
        }
    );
}

Command* CreateLookEquipment() {
    return new Command(
        { {0, {"equipment"}} },
        [](Game& game, const vector<string>& args) {
            Player* player = game.GetPlayer();
            Weapon* weapon = player->GetEquippedWeapon();

            cout << "You are currently wielding: " << (weapon ? weapon->GetName() : "nothing") << endl;
            cout << "You are currently wearing: " << endl;

            Equipment* helmet = player->GetEquippedArmor(ArmorPart::Head);
            Equipment* chest = player->GetEquippedArmor(ArmorPart::Chest);
            Equipment* legs = player->GetEquippedArmor(ArmorPart::Legs);
            Equipment* arms = player->GetEquippedArmor(ArmorPart::Arms);
            Equipment* boots = player->GetEquippedArmor(ArmorPart::Feet);

            cout << "- Helmet: " << (helmet ? helmet->GetName() : "nothing") << endl;
            cout << "- Chest: " << (chest ? chest->GetName() : "nothing") << endl;
            cout << "- Legs: " << (legs ? legs->GetName() : "nothing") << endl;
            cout << "- Arms: " << (arms ? arms->GetName() : "nothing") << endl;
            cout << "- Boots: " << (boots ? boots->GetName() : "nothing") << endl;
        }
    );
}

Command* CreateCloseCommand() {
	return new Command(
		{ {0, {"close"}} },
		[](Game& game, const vector<string>& args) {
			Room* current = game.GetPlayer()->GetCurrentRoom();

            RestrictedExit* restExit = FindInList<Exit, RestrictedExit>(current->GetExits(), args[0]);
            if (restExit && restExit->IsOpen()) {
                restExit->Close();
            }

            Container* container = FindInList<Object, Container>(current->GetInventory(), args[0]);
            if (container && container->IsOpen()) {
				container->Close();
				cout << "You close the " << container->GetName();
				return;
			}

            Container* inventoryContainer = FindInList<Item, Container>(game.GetPlayer()->GetInventory(), args[0]);
            if (container && container->IsOpen()) {
                container->Close();
            }
		}
	);
}

Command* CreateQuitCommand() {
    return new Command(
        { {0, {"quit", "exit"}} },
        [](Game& game, const vector<string>& args) {
            cout << "Thanks for playing! Goodbye!\n";
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
        CreateEquipCommand(),
        CreateUnequipCommand(),
        CreateQuitCommand(),
        CreateLookEquipment(),
        CreateDisplayCommand({"help"}, "Available commands: look, go, take, drop, inventory, help"),
        CreateDisplayCommand({"bar"}, "Bar bar"),
        CreateDisplayCommand({"Zork"}, "At your service"),
        CreateDisplayCommand({"jump"}, "Are you proud of yourself?"),
        CreateDisplayCommand({"shout", "yell" , "scream"}, "Aaaarrrrgggghhhh!"),
        CreateDisplayCommand({"hello"}, "Hello"),
    };
}