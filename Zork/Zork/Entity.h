#ifndef __Entity__
#define __Entity__

using namespace std;

#include <string>
#include <vector>

class Entity {
public:
    Entity(const string& name, const string& description);
    virtual ~Entity() = default;
    string GetName() const;
    string GetDescription() const;

    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);
    const vector<Entity*>& GetEntities();

private:
    string name;
    string description;
    vector<Entity*> contains; 
};

#endif