#include <iostream>
#include <string>
#include "World.h"

using namespace std;

int main() {

    string command;

    cout << "Welcome to Zork I: Made by Miquel Barbarà Garrido!" << endl;

    World world;

    while (true) {
        cout << "\n>";
        getline(cin, command);

        if (command == "quit") {
			cout << "Thank you for playing Zork I!" << endl;
			break;
		} else if (command == "help") {
			cout << "Available commands: quit" << endl;
		} else {
			cout << "Unknown command: " << command << endl;
		}
    }

	cout << "Exiting the game..." << endl;

    return 0;
}