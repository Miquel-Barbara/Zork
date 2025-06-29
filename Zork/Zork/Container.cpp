#include "Container.h"


Container::Container(const string& name, const string& description, vector<Item*> initialItems)
	: Object(name, description) {
	inventory = initialItems;
}

bool Container::AddItem(Item* item) {
	if (isOpen) {
		return Inventory<Item>::AddItem(item);
	}
	else {
		cout << "The container is closed. You cannot add items." << endl;
		return false;
	}
}

bool Container::RemoveItem(Item* item) {
	if (isOpen) {
		return Inventory<Item>::RemoveItem(item);
	}
	else {
		cout << "The container is closed. You cannot remove items." << endl;
		return false;
	}
}