#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "BanglaUtf8.hpp"
#include "CommandLine.hpp"

int main (int argc, char ** argv) {
    CommandLine arguments(argc, argv);

    if (arguments.present("inputFile")) {
        std::ifstream inputFile(arguments.get("inputFile"));
        BanglaUtf8 converter;
        converter.convert(inputFile);
        converter.print(std::cout);

        return 0;
    }

    arguments.print_usage();
    return 0;
}
