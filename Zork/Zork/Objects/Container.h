#ifndef __Container__
#define __Container__

#include <vector>
#include "Item.h"
#include "../Inventory.h"
#include "../Others/Openable.h"

class Container: public virtual Object, public Inventory<Item>, public Openable {
public:
    Container(const string& name, const string& description, vector<Item*> initialItems);
    virtual ~Container() = default;
    bool AddItem(Item* item) override;
    bool RemoveItem(Item* item) override;
protected:
    int size = 1;
};

#endif
