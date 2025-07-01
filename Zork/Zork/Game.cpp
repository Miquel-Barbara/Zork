#include "Game.h"
#include "Enums/StatType.h"

Game::Game() {
    commandFactory = new CommandFactory();
    
    player = new Player("Player", "You are the main character of the game.", 
		{
			{StatType::Hp, new StatValue(100)},
			{StatType::Strength, new StatValue(10)},
			{StatType::Defense, new StatValue(5)},
			{StatType::Speed, new StatValue(3)},
			{StatType::Evasion, new StatValue(7)},
            {StatType::Accuracy, new StatValue(50)},
		}
        );

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