#include "Entity.h"

Entity::Entity(const string& name, const string& description)
	: name(name), description(description) {}

string Entity::GetName() const {
	return name;
}

string Entity::GetDescription() const {
	return description;
}

void Entity::AddEntity(Entity* entity) {
	contains.push_back(entity);
}

void Entity::RemoveEntity(Entity* entity) {
	auto it = find(contains.begin(), contains.end(), entity);
	if (it != contains.end()) {
		contains.erase(it);
	}
}

const vector<Entity*>& Entity::GetEntities() {
	return contains;
}
