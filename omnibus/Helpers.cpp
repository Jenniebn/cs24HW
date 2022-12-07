
#include "Helpers.h"
#include <string>
#include <limits.h>

// Space to implement helper class member functions.

STATION::STATION(string name, size_t num){
    statName = name;
    dist = num;
}

STATION::EDGE::EDGE(int distance, string name, STATION* pre, STATION* n){
    dist = distance;
    lineName = name;
    previous = pre;
    next = n;
}


Entry::Entry(size_t distance, STATION* stat, string line){
    dist = distance;
    station = stat;
    lineName = line;
}