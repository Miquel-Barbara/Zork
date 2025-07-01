#ifndef __RestrictedExit__
#define __RestrictedExit__

using namespace std;

#include <string>
#include <map>
#include "../Enums/Direction.h"
#include <vector>
#include "Exit.h"
#include "../Others/Openable.h"

class Game;

class RestrictedExit : public Exit, public Openable {
public:
    RestrictedExit(const string& name, const string& description, Direction direction, Room* source, Room* destination,
        const string& descriptionOpen,
        const string& descriptionClose,
        const string& openText,
        const string& closeText,
        const string& blockedText,
        shared_ptr<bool> isOpen, 
        bool canOpen = true);

    string GetDescription();

    void MoveToDestination(Creature* creature) const override;

private:

};

#endif
