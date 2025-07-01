#ifndef __Item__
#define __Item__

#include "../Entity.h"
#include "Object.h"

class Item : public virtual Object {
public:
    Item(const string& name, const string& description);
private:

};

#endif
