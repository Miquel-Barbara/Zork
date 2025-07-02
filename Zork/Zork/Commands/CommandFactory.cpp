#include "CommandFactory.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include "CommandGenerator.h"
#include "../Utils.h"
#include <set>

CommandFactory::CommandFactory() {
    commands = GenerateAllCommands();
}


Command* CommandFactory::DetectCommand(const string& input, vector<string>& finalArgs) {

    string inputLowerCase = toLower(input);
    vector<string> args = SplitInput(inputLowerCase);

    if (args.empty()) {
        return nullptr;
    }

    for (Command* command : commands) {
        map<int, vector<string>> pattern = command->GetPattern();
        map<int, string> foundPattern = MatchPattern(args, pattern);

        if (foundPattern.size() == pattern.size()) {
            vector<string> combinedArgs = CombineArguments(args, foundPattern);
            finalArgs = combinedArgs;
            return command;
        }
    }

    return nullptr;
}

vector<string> CommandFactory::SplitInput(const string& input) {
    istringstream iss(input);
    string word;
    vector<string> args;

    while (iss >> word) {
        args.push_back(word);
    }

    return args;
}

map<int, string> CommandFactory::MatchPattern(const vector<string>& args, const map<int, vector<string>>& pattern) {
    map<int, string> foundPattern;
    set<string> matchedWords;

    for (const auto& pair : pattern) {
        const vector<string>& expectedWords = pair.second;

        for (int i = 0; i < args.size(); ++i) {
            if (foundPattern.find(i) != foundPattern.end()) continue;
            if (matchedWords.count(args[i])) continue;

            if (find(expectedWords.begin(), expectedWords.end(), args[i]) != expectedWords.end()) {
                foundPattern[i] = args[i];
                matchedWords.insert(args[i]);
                break;
            }
        }
    }

    return foundPattern;
}

vector<string> CommandFactory::CombineArguments(vector<string>& args, const map<int, string>& foundPattern) {
    vector<string> result;
    int lastKeywordIndex = -1;

    for (int i = 0; i < args.size(); ++i) {
        if (foundPattern.find(i) != foundPattern.end()) {
            lastKeywordIndex = i;
            continue;
        }
        if (!result.empty() && i == lastKeywordIndex + 1) {
            result.push_back(args[i]);
        }
        else if (!result.empty()) {
            result.back() += " " + args[i];
        }
        else {
            result.push_back(args[i]);
        }
    }
    return result;
}