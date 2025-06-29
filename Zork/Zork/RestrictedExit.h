#ifndef __RestrictedExit__
#define __RestrictedExit__

using namespace std;

#include <string>
#include <map>
#include "Direction.h"
#include <vector>
#include "Exit.h"
#include "Openable.h"

class Game;

class RestrictedExit : public Exit, public Openable {
public:
    RestrictedExit(Direction direction, Room* source, Room* destination,
        const string& descriptionOpen,
        const string& descriptionClose,
        const string& openText,
        const string& closeText,
        const string& blockedText,
        shared_ptr<bool> isOpen, 
        bool canOpen = true);

    string GetDescription() const;

    void MoveToDestination(Creature* creature) const override;

private:

};

#endif
