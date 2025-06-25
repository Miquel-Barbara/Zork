#include "Game.h"
#include <sstream>
#include <iostream>
#include "Commands/Command.h"
#include "Commands/MoveCommand.h"
#include "Commands/LookCommand.h"

Game::Game() {
    RegisterCommand(new LookCommand());
    RegisterCommand(new MoveCommand());

    world = new World();
    currentRoom = world->GetStartRoom();
}

Room* Game::GetCurrentRoom() const {
    return currentRoom;
}

void Game::SetCurrentRoom(Room* room) {
    cout << room->GetName() << "\n";
    cout << room->GetDescription() << "\n";
    currentRoom = room;
}

void Game::RegisterCommand(Command* command) {
    commands[command->GetName()] = command;
}

void Game::ProcessInput(const string& input) {
    istringstream iss(input);
    string word;
    vector<string> args;

    while (iss >> word) {
        args.push_back(word);
    }

    if (args.empty()){
		cout << "I beg your pardon?\n";
		return;
	}

    auto it = commands.find(args[0]);
    if (it != commands.end()) {
        it->second->Execute(*this, args);
    }
    else {
        cout << "That's not a verb I recognise.\n";
    }
}