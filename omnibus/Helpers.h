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
        
        EDGE(int distance, string name);
        ~EDGE();
        // bool operator < (const EDGE& other) const {
        //     return this -> dist > other.dist;
        // }
    };
    string statName;
    size_t dist;
    vector <EDGE*> edge;

    STATION(string name, size_t num);
    ~STATION();
    
};



struct Entry {
    size_t dist;
    STATION* station = nullptr;
    Entry* previous = nullptr;
    string lineName;

    Entry(size_t distance, STATION* stat, Entry* pre, string line);

    bool operator < (const Entry& other) const {
        return this -> dist > other.dist;
    }
};



#endif