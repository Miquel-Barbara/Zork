#include "Game.h"

Game::Game() {
    commandFactory = new CommandFactory();
    
    player = new Player("Player", "You are the main character of the game.");

    world = new World();
    player->Move(world->GetStartRoom());
}

Player* Game::GetPlayer() {
	return player;
}

void Game::ProcessInput(const string& input) {
    vector<string> args;
    Command* command = commandFactory->DetectCommand(input, args);

    if (command) {
        command->Execute(*this, args);
    }
    else {
        cout << "That's not a verb I recognise.\n";
    }
}