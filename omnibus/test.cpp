#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::istringstream
using namespace std;
#include "Atlas.h"
#include <fstream>
#include <stdexcept>

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cout << "USAGE: " << argv[0] << " [data-file]\n";
        std::exit(1);
    }
    

    Atlas* atlas = nullptr;
    try {
        std::ifstream file(argv[1]);
        if(file.fail()) {
            throw std::runtime_error("Could not open file.");
        }

        atlas = Atlas::create(file);
    }
    catch(const std::exception& e) {
        std::cout << "Error reading file: " << e.what() << '\n';
        std::exit(1);
    }


    delete atlas;
    return 0;
}