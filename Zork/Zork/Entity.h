#ifndef __ENTITY_H__
#define __ENTITY_H__

using namespace std;

#include <string>
#include <vector>
#include <iostream>

class Entity {
public:
    Entity(const string& name, const string& description);
    string GetName() const;
    virtual string GetDescription() const;
private:
    string name;
    string description;
};

#endif