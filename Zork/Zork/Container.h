#ifndef __Container__
#define __Container__

#include <vector>
#include "Item.h"
#include "Inventory.h"
#include "Openable.h"

class Container: public Object, public Inventory<Item>, public Openable {
public:
    Container(const std::string& name, const std::string& description);
    virtual ~Container() = default;
    bool AddItem(Item* item) override;
    bool RemoveItem(Item* item) override;
protected:
    int size = 1;
};

#endif
