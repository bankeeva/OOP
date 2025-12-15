#include <iostream>
#include <fstream>
#include "parser.h"

int main() {
    std::ifstream file("test.csv");
    if (!file) {
        std::cout << "cannot open file\n";
        return 1;
    }

    CSVConfig cfg;
    CSVParser<std::string, std::string> parser(file, 0, cfg);

    try {
        for (auto t : parser)
            std::cout << t << "\n";
    }
    catch (const CSVError& e) {
        std::cout << "CSV error: " << e.what() << "\n";
    }
}


// build
// make -j
// ctest --output-on-failure
