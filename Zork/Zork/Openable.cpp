#include "Openable.h"

bool Openable::IsOpen() {
    return *isOpen;
}

void Openable::Open() {
    cout << openText + "\n" << endl;
    if (!*isOpen && canOpen) {
        *isOpen = true;
    }
}

void Openable::Close() {
    if (*isOpen) {
        *isOpen = false;
        cout << closeText + "\n" << endl;
    }
}