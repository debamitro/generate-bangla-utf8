#ifndef COMMAND_LINE_HPP
#define COMMAND_LINE_HPP

#include <unordered_map>
#include <string>

class CommandLine {
public:
    CommandLine(int argc, char ** argv);
    ~CommandLine() = default;

    bool present(const char * argName) const;
    std::string get(const char * argName) const;

    void print_usage() const;
private:
    std::unordered_map<std::string, std::string> argumentValues_;
    std::string exeName_;
};

#endif
