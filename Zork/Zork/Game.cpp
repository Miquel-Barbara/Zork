#include "Game.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include "Commands/Command.h"
#include "Commands/MoveCommand.h"
#include "Commands/LookCommand.h"
#include "Commands/Inventory/TakeCommand.h"
#include "Commands/Inventory/DropCommand.h"
#include "Commands/Inventory/InventoryCommand.h"

Game::Game() {
    RegisterCommand(new LookCommand());
    RegisterCommand(new MoveCommand());
    RegisterCommand(new DropCommand());
    RegisterCommand(new TakeCommand());
    RegisterCommand(new InventoryCommand());

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
    commands.push_back(command);
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

    // Iterate through the commands and check if any match the input
    for (Command* command : commands) {
        map<int, string> pattern = command->GetPattern();
        map<int, string> foundPattern;
        
        // Check if the keyword match with the pattern and where
        for (const pair<const int, string>& pair : pattern) {
            const string& keyword = pair.second;

            for (int i = 0; i < args.size();i++) {
                if (args[i] == keyword) {
                    // This is the position where the pattern was found
					foundPattern[i] = keyword;
					break;
				}
            }
        }

        if (foundPattern.size() != pattern.size())
            continue;

        // Extract meaningful arguments by skipping keywords
        vector<string> newArgs;
        vector<int> patternIndices;

        for (const pair<const int, string>& pair : pattern) {
            patternIndices.push_back(pair.first);
        }


        // Sort indices to detect arguments between them
        sort(patternIndices.begin(), patternIndices.end());

        for (size_t i = 0; i < patternIndices.size(); ++i) {
            int current = patternIndices[i];
            int next = (i + 1 < patternIndices.size()) ? patternIndices[i + 1] : args.size();

            // Capture words between current and next keyword
            int start = current + 1;
            if (i == 0 && current > 0) {
                start = 0;
                current = patternIndices[0];
            }

            string segment;
            for (int j = start; j < next; ++j) {
                if (foundPattern.find(j) != foundPattern.end()) continue; // Skip keywords
                if (!segment.empty()) segment += " ";
                segment += args[j];
            }

            if (!segment.empty())
                newArgs.push_back(segment);
        }

        // Match successful — execute the command
        command->Execute(*this, newArgs);
        return;
    }

    cout << "That's not a verb I recognise.\n";
}