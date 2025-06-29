#include "RestrictedExit.h"

RestrictedExit::RestrictedExit(const string& name, const string& description, Direction direction, Room* source, Room* destination,
    const string& descriptionOpen,
    const string& descriptionClose,
    const string& openText,
    const string& closeText,
    const string& blockedText,
    shared_ptr<bool> isOpen,
    bool canOpen)
    : Exit(name, description, direction, source, destination) {
    this->descriptionOpen = descriptionOpen;
    this->descriptionClose = descriptionClose;
    this->openText = openText;
    this->closeText = closeText;
    this->blockedText = blockedText;
    this->isOpen = isOpen;
    this->canOpen = canOpen;
}

string RestrictedExit::GetDescription() {
	if(IsOpen())
		return descriptionOpen;
	else
		return descriptionClose;
}

void RestrictedExit::MoveToDestination(Creature* creature) const {
	if (*isOpen) {
		Exit::MoveToDestination(creature);
	} else {
		cout << blockedText + "\n" << endl;
	}
}