#include <iostream>
#include <sstream>
#include <string>
#include "BanglaUtf8.hpp"

int main () {
    BanglaUtf8 converter;
    std::string input = "kaku kAk";
    std::stringstream inputChars(input);
    converter.convert(inputChars);
    converter.print();
    std::cout << "\n";
    return 0;
}
