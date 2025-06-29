#ifndef __Object__
#define __Object__

#include "Entity.h"

class Object : public Entity {
public:
    Object(const string& name, const string& description);
    virtual ~Object() = default;
};

#endif
