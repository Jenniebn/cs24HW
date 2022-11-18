#include "StarMap.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

// Use this file to test your Heap class!
// This file won't be graded - do whatever you want.

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cout << "USAGE: " << argv[0] << " [data-file]\n";
        std::exit(1);
    }
    StarMap* map;

    try {
        std::ifstream file(argv[1]);
        map = StarMap::create(file);
    }
    catch(const std::exception& e) {
        std::cout << "Error reading file: " << e.what() << '\n';
        std::exit(1);
    }
    //map -> print();
    vector<Star> vect;
    vect = map -> find(2, 1, 0, -1);
    for (size_t i = 0; i < 2; i++){
        cout << "x: " << vect[i].x << "y: " << vect[i].y << "z: " << vect[i].z << endl;
    }
   
    return 0;
}

//((-  x: 0.5y: -0.5z: -0.5 (-  x: 0.5y: -0.5z: 0.5 (-  x: 0.5y: 0.5z: -0.5  x: 0.5y: 0.5z: 0.5)))  x: -0.5y: -0.5z: -0.5 (-  x: -0.5y: -0.5z: 0.5 (-  x: -0.5y: 0.5z: -0.5  x: -0.5y: 0.5z: 0.5)))
