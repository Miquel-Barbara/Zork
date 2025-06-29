#ifndef __ItemContainer__
#define __ItemContainer__

#include "Entity.h"
#include "Object.h"
#include "Item.h"
#include "Container.h"

class ItemContainer : public Item, public Container {
public:
    ItemContainer(const string& name, const string& description, vector<Item*> initialItems);
private:

};

#endif