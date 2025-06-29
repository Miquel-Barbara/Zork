#ifndef __CommandFactory__
#define __CommandFactory__

using namespace std;

#include <string>
#include <vector>
#include <map>
#include "Command.h"

class Command;

class CommandFactory {
public:
    CommandFactory();
    Command* DetectCommand(const string& input, vector<string>& finalArgs);

private:
    vector<Command*> commands;

    vector<string> SplitInput(const string& input);
    map<int, string> MatchPattern(const vector<string>& args, const map<int, vector<string>>& pattern);
    vector<string> CombineArguments(vector<string>& args, const map<int, string>& foundPattern);
};

#endif
