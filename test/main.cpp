#include <iostream>
#include <sstream>
#include <string>
#include "BanglaUtf8.hpp"

static bool verify_conversion (const char * text, const char * bangla) {
    BanglaUtf8 converter;
    std::stringstream inputChars;
    inputChars << text;
    converter.convert(inputChars);

    std::stringstream outputStream;
    converter.print(outputStream);

    if (outputStream.str() == bangla) {
        std::cout << "conversion successful for " << text << "\n";
        return true;
    }
    else {
        std::cout << "conversion bad (" << outputStream.str()
                  << ") for " << text << "\n";
        return false;
    }
}

int main () {
    int numPasses = 0;
    numPasses += verify_conversion ("kAku",u8"\u0995\u09BE\u0995\u09C1");
    numPasses += verify_conversion ("gAdhA",u8"\u0997\u09BE\u09A7\u09BE");
    std::cout << numPasses << " tests passed\n";
    return 0;
}
