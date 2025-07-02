#include "Game.h"
#include "Enums/StatType.h"
#include <algorithm>


Game::Game() {
    commandFactory = new CommandFactory();
    
    player = new Player("Player", "", 
		{
			{StatType::Hp, new StatValue(100)},
			{StatType::Strength, new StatValue(10)},
			{StatType::Defense, new StatValue(5)},
			{StatType::Speed, new StatValue(3)},
			{StatType::Evasion, new StatValue(7)},
            {StatType::Accuracy, new StatValue(70)},
		}
        );

    world = new World();
    player->Move(world->GetStartRoom());
}

void Game::Tick() {
    world->Tick();

    if (player->IsDead()) {
        cout << "I mean... How you even die in this game? Skill issue? Bad luck? I know you can do it better." << endl;
        Quit();
    }

    if (player->GetCurrentRoom() == world->GetFinalRoom()) {
        cout << "Congrats you beat the game, I hope you enjoied playing as much as me making it!" << endl;
        Quit();
    }
}

Player* Game::GetPlayer() {
	return player;
}

void Game::ProcessInput(const string& input) {
    vector<string> args;
    Command* command = commandFactory->DetectCommand(input, args);

    if (command) {
        if (command->ItTicks()) Tick();
        command->Execute(*this, args);
    }
    else {
        cout << "That's not a verb I recognise.\n";
    }
}

bool Game::EndGame() const {
	return quit;
}