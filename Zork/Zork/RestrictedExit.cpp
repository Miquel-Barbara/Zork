#include "RestrictedExit.h"

RestrictedExit::RestrictedExit(Direction direction, Room* source, Room* destination,
    const string& descriptionOpen,
    const string& descriptionClose,
    const string& openText,
    const string& closeText,
    const string& blockedText,
    shared_ptr<bool> isOpen,
    bool canOpen)
    : Exit(direction, source, destination){
    this->descriptionOpen = descriptionOpen;
    this->descriptionClose = descriptionClose;
    this->openText = openText;
    this->closeText = closeText;
    this->blockedText = blockedText;
    this->isOpen = isOpen;
    this->canOpen = canOpen;
}

string RestrictedExit::GetDescription() const {
	if(isOpen)
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