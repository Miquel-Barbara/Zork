#include "ItemContainer.h"

ItemContainer::ItemContainer(const string& name, const string& description, vector<Item*> initialItems): Item(name, description), Container(name, description, initialItems) {
}