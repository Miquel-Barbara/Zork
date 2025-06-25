#include <iostream>
#include <string>
#include "Game.h"


using namespace std;

int main() {

    string input;

    cout << "Welcome to Zork I: Made by Miquel Barbara Garrido!" << endl;

    Game game;

    while (true) {
        cout << "\n>";
        getline(cin, input);

        game.ProcessInput(input);
    }

	cout << "Exiting the game..." << endl;

    return 0;
}