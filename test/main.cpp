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
                  << ") for " << text << " (expected " << bangla << ")\n";
        return false;
    }
}

int main () {
    int numPasses = 0;
    numPasses += verify_conversion ("kAku",u8"\u0995\u09BE\u0995\u09C1");
    numPasses += verify_conversion ("gAdhA",u8"\u0997\u09BE\u09A7\u09BE");
    numPasses += verify_conversion ("bA;lA bhAShA",u8"\u09AC\u09BE\u0982\u09B2\u09BE \u09AD\u09BE\u09B7\u09BE");
    numPasses += verify_conversion ("boishAkh",u8"\u09AC\u09C8\u09B6\u09BE\u0996");
    std::cout << numPasses << " tests passed\n";
    return 0;
}
