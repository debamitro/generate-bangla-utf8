#include <iostream>
#include <sstream>
#include <string>
#include "BanglaUtf8.hpp"

int main () {
    BanglaUtf8 converter;
    std::string input = "kAku mAmu dAdu thAma theme thAk";
    std::stringstream inputChars(input);
    converter.convert(inputChars);
    converter.print(std::cout);
    std::cout << "\n";
    return 0;
}
