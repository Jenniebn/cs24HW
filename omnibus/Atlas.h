#ifndef ATLAS_H
#define ATLAS_H
#include <set>
#include <istream>
#include <string>
#include "Helpers.h"
#include "Trip.h"
#include "Helpers.h"
#include <map>
#include <queue>  
#include <utility> 
#include <vector>


class Atlas {
public:
    // Required Class Function
    static Atlas* create(std::istream& stream);

private:
    // Member Variables
    STATION* prePtr = nullptr;

    map<string, bool> unvisited;
    map<string, int> shortToA; // shortest distance from source
    map<string, STATION*> mp; // graph of stations

    priority_queue<Entry> myHeap;
public:
    // Constructor & Destructor
    Atlas(std::istream& stream);
    ~Atlas();

    // Required Member Function
    Trip route(const std::string& src, const std::string& dst);
    STATION* dijkstra(string source, string destination);
};

#endif