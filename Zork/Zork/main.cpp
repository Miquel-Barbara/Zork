#include <iostream>
#include <string>
#include "Game.h"
#include "Utils.h"


using namespace std;

int main() {

    string input;

    cout << "Welcome to Zork I: Made by Miquel Barbara Garrido!" << endl;
    InitRandom();
    Game game;

    while (!game.EndGame()) {
        cout << "\n>";
        getline(cin, input);
        game.ProcessInput(input);
    }

	cout << "Exiting the game..." << endl;

    return 0;
}