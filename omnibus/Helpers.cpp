#include "Helpers.h"
#include <string>

// Space to implement helper class member functions.

STATION::STATION(string name, size_t num){
    statName = name;
    dist = num;
}

STATION::EDGE::~EDGE(){
    delete previous;
    delete next;
}

Entry::~Entry(){
    delete station;
    delete previous;
}
