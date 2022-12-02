#ifndef HELPERS_H
#define HELPERS_H
#include <vector>
#include <string>
#include <limits.h>
using namespace std;

// If you want to add any helper classes,
// here's some space to do it in.


struct STATION {
    struct EDGE {
        int dist;
        string lineName;
        STATION* previous = nullptr;
        STATION* next = nullptr;
        bool train = true;

        ~EDGE();
        // bool operator < (const EDGE& other) const {
        //     return this -> dist > other.dist;
        // }
    };
    string statName;
    size_t dist;
    vector <EDGE*> edge;

    STATION(string name, size_t num);
    
};



struct Entry {
    size_t dist = INT_MAX;
    STATION* station = nullptr;
    Entry* previous = nullptr;
    string lineName;

    ~Entry();

    bool operator < (const Entry& other) const {
        return this -> dist > other.dist;
    }
};



#endif
