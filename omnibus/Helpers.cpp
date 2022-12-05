#include "Helpers.h"
#include <string>
#include <limits.h>

// Space to implement helper class member functions.

STATION::STATION(string name, size_t num){
    statName = name;
    dist = num;
}

STATION::~STATION(){
    for ( auto i : edge){
        delete i;
    }
}

STATION::EDGE::EDGE(int distance, string name){
    dist = distance;
    lineName = name;
}

// STATION::EDGE::~EDGE(){
//     delete previous;
//     delete next;
// }

Entry::Entry(size_t distance, STATION* stat, Entry* pre, string line){
    dist = distance;
    station = stat;
    previous = pre;
    lineName = line;
}
