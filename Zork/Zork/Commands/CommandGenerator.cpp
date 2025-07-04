#include "CommandGenerator.h"
#include "../World/RestrictedExit.h"
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
        }, false
    );
}

Command* CreateTakeCommand() {
    return new Command(
        { {0, {"take", "get", "grab"}} },
        [](Game& game, const vector<string>& args) {
            string itemName = args[0];
            Room* current = game.GetPlayer()->GetCurrentRoom();
            vector<Entity*> entities = current->GetInventory();

            Item* item = FindInList<Entity, Item>(entities, itemName);
            if (item) {
				game.GetPlayer()->AddItem(item);
				current->RemoveItem(item);
            }
            else {
                for (Entity* obj : entities) {
                    Container* container = dynamic_cast<Container*>(obj);
                    if (container && container->IsOpen()) {
                        // Check if the container has the item
                        Item* item = FindInList<Item, Item>(container->GetInventory(), itemName);
                        if (item) {
                            game.GetPlayer()->AddItem(item);
                            container->RemoveItem(item);
                            cout << "Taken." << endl;
                            return;
                        }
                    }
                }
            }

            if (item) {
                cout << "Taken." << endl;
            }
            else {
                cout << "You can't see any such thing." << endl;
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
                    cout << "You don't have items.\n";
                }

                Room* current = game.GetPlayer()->GetCurrentRoom();
                for (Item* item : inventory) {
                    inventory.erase(remove(inventory.begin(), inventory.end(), item), inventory.end());
                    current->AddItem(item);
                    game.GetPlayer()->RemoveItem(item);
                    cout << item->GetName() + " : Dropped";
                }
                cout << "\n";
                inventory.clear();
                return;
            }
            else {
                for (auto it = inventory.begin(); it != inventory.end(); ++it) {
                    if ((*it)->GetName() == target) {
                        Item* item = *it;
                        game.GetPlayer()->RemoveItem(item);
                        game.GetPlayer()->GetCurrentRoom()->AddItem(item);
                        cout << "Dropped.\n";
                        return;
                    }
                }

                cout << "You can't see any such thing.\n";
            }
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
        }, false
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
        }, false
    );
}

Command* CreateDisplayCommand(vector<string> keyword, string message) {
	return new Command(
        { {0, keyword} },
		[message](Game& game, const vector<string>& args) {
			cout << message << endl;
		}, false
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

            Container* container = FindInList<Entity, Container>(current->GetInventory(), args[0]);
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
            Equipment* itemToUnequip = FindInList<Equipment, Equipment>(game.GetPlayer()->GetAllEquipment(), args[0]);

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
        }, false
    );
}

Command* CreateStatsCommand() {
	return new Command(
		{ {0, {"stats"}} },
		[](Game& game, const vector<string>& args) {
			Player* player = game.GetPlayer();
			cout << "Your stats:" << endl;
            for (StatType statType : player->GetAllStats()) {
                cout << "- " << StatToString(statType) +": "+ to_string(player->GetStat(statType)) << endl;
            }
		}, false
	);
}

Command* CreateStatCommand() {
    return new Command(
        { {0, {"check"}} },
        [](Game& game, const vector<string>& args) {
            Player* player = game.GetPlayer();
            StatType statType = StringToStat(args[0]);
            if(statType){
                cout << "You have" << StatToString(statType) + ": " + to_string(player->GetStat(statType)) << endl;
            }
			else {
				cout << "Invalid stat type.\n";
			}
        }, false
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

            Container* container = FindInList<Entity, Container>(current->GetInventory(), args[0]);
            if (container && container->IsOpen()) {
				container->Close();
				cout << "You close the " << container->GetName();
				return;
			}

            Container* inventoryContainer = FindInList<Item, Container>(game.GetPlayer()->GetInventory(), args[0]);
            if (container && container->IsOpen()) {
                container->Close();
            }

            cout << "\n";
		}
	);
}

Command* CreateQuitCommand() {
    return new Command(
        { {0, {"quit", "exit"}} },
        [](Game& game, const vector<string>& args) {
            game.Quit();
            cout << "Thanks for playing! Goodbye!\n";
        }, false
    );
}

Command* CreatePutIntoCommand() {
    return new Command(
        { {0, {"put"}} , {2 , {"into"}} },
        [](Game& game, const vector<string>& args) {
    
			string itemName = args[0];
			string containerName = args[1];

			Item* item = FindInList<Item, Item>(game.GetPlayer()->GetInventory(), itemName);
			if (!item) {
				cout << "You don't have that item in your inventory.\n";
				return;
			}

			Container* container = FindInList<Entity, Container>(game.GetPlayer()->GetCurrentRoom()->GetInventory(), containerName);
			if (!container || !container->IsOpen()) {
				cout << "You can't put items into that object.\n";
				return;
			}

			game.GetPlayer()->RemoveItem(item);
			container->AddItem(item);
			cout << "You put the " << item->GetName() << " into the " << container->GetName() << ".\n";
		}
    );
}

Command* CreateAttackCommand() {
    return new Command(
        { {0, {"attack"}} },
        [](Game& game, const vector<string>& args) {
            vector<Entity*> entities = game.GetPlayer()->GetCurrentRoom()->GetInventory();
            Enemy* enemy = FindInList<Entity, Enemy>(entities, args[0]);

            if (enemy) {
                game.GetPlayer()->Attack(enemy);
                if (enemy->IsDead()) {
                    enemy->Die();
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
        CreateEquipCommand(),
        CreateUnequipCommand(),
        CreateQuitCommand(),
        CreateLookEquipment(),
        CreateStatsCommand(),
        CreateStatCommand(),
        CreatePutIntoCommand(),
        CreateAttackCommand(),
        CreateDisplayCommand({"help"}, "Available commands: look, go, take, drop, inventory, help"),
        CreateDisplayCommand({"bar"}, "Bar bar"),
        CreateDisplayCommand({"Zork"}, "At your service"),
        CreateDisplayCommand({"jump"}, "Are you proud of yourself?"),
        CreateDisplayCommand({"shout", "yell" , "scream"}, "Aaaarrrrgggghhhh!"),
        CreateDisplayCommand({"hello"}, "Hello"),
    };
}