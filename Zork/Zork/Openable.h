#ifndef __Openable__
#define __Openable__

#include <memory>
#include <string>
#include <iostream>

using namespace std;

class Openable {
public:
    virtual ~Openable() = default;

    virtual void Open();
    virtual void Close();
    virtual bool IsOpen();

    string GetBlockedText() const { return blockedText; }

protected:
    shared_ptr<bool> isOpen = make_shared<bool>(false);
    bool canOpen;

    string blockedText;
    string descriptionOpen;
    string descriptionClose;
    string openText;
    string closeText;
};

#endif
