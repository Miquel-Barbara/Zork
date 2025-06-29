#ifndef __Inventory__
#define __Inventory__

#include <vector>
#include "Objects/Item.h"

using namespace std;
template<typename ObjectType>

class Inventory {
public:
    Inventory() = default;
    virtual ~Inventory() = default;

    virtual bool AddItem(ObjectType* item);
    virtual bool RemoveItem(ObjectType* item);
    bool HasItem(const ObjectType* item) const;
    const vector<ObjectType*>& GetInventory() const;

protected:
    vector<ObjectType*> inventory;
    int maxItems = 10;
};

template<typename ObjectType>
bool Inventory<ObjectType>::AddItem(ObjectType* item) {
	if (inventory.size() < maxItems) {
		inventory.push_back(item);
		return true;
	}
	else {
		cout << "Inventory is full. Cannot add item: " << item->GetName() << endl;
		return false;
	}
}

template<typename ObjectType>
bool Inventory<ObjectType>::RemoveItem(ObjectType* item) {
	auto it = find(inventory.begin(), inventory.end(), item);
	if (it != inventory.end()) {
		inventory.erase(it);
		return true;
	}
	return false;
}

template<typename ObjectType>
bool Inventory<ObjectType>::HasItem(const ObjectType* item) const {
	return find(inventory.begin(), inventory.end(), item) != inventory.end();
}

template<typename ObjectType>
const vector<ObjectType*>& Inventory<ObjectType>::GetInventory() const {
	return inventory;
}

#endif
