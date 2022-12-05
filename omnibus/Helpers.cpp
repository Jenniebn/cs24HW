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

Entry::Entry(size_t distance, STATION* stat, Entry* pre, string line){
    dist = distance;
    station = stat;
    previous = pre;
    lineName = line;
}

// STATION::~STATION(){
//     for ( auto i : edge){
//         delete i.previous;
//         delete i.next;
//     }
// }
