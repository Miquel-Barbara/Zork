#include "Entity.h"

Entity::Entity(const string& name, const string& description)
	: name(name), description(description) {}

string Entity::GetName() const {
	return name;
}

string Entity::GetDescription() const {
	return description;
}
