#include "CommandLine.hpp"
#include <unordered_map>
#include <string>
#include <iostream>

CommandLine::CommandLine(int argc, char ** argv) : exeName_(argv[0]) {
    bool foundFileName = false;
    for (int i = 1; i < argc; ++i) {
        if (argv[i][0] == '-') {
            // Handle - options
        }
        else if (!foundFileName) {
            argumentValues_.insert(std::make_pair(std::string("inputFile"), std::string(argv[i])));
            foundFileName = true;
        }
    }
}

bool CommandLine::present(const char * argName) const {
    return argumentValues_.find(std::string(argName)) != argumentValues_.end();
}

std::string CommandLine::get(const char * argName) const {
    return argumentValues_.find(std::string(argName))->second;
}

void CommandLine::print_usage() const {
    std::cout << "Usage: " << exeName_ << " <input-file>\n";
    std::cout << "(If there is no input file then stdin is assumed to be the input)\n";
}
