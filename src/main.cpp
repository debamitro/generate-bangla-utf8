#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "BanglaUtf8.hpp"
#include "CommandLine.hpp"

int main (int argc, char ** argv) {
    CommandLine arguments(argc, argv);

    BanglaUtf8 converter;
    if (arguments.present("inputFile")) {
        if (arguments.get("inputFile") == "-") {
            converter.convert(std::cin);
        }
        else {
            std::ifstream inputFile(arguments.get("inputFile"));
            converter.convert(inputFile);
        }
        converter.print(std::cout);

        return 0;
    }

    arguments.print_usage();
    return 0;
}
