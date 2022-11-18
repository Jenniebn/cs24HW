#ifndef STARMAP_H
#define STARMAP_H
#include <queue>  
#include "Star.h"
#include "Helpers.h"
#include <istream>
#include <vector>

class StarMap {
public:
    // Required Class Function
    static StarMap* create(std::istream& stream); 
    
    
private:
    // Member Variables
    Node* tree;
    size_t index = 1;
    size_t depth = 0;
    priority_queue<Entry> myQueue;
public:
    // Constructor & Destructor
    StarMap(std::istream& stream); 
    ~StarMap();

    // Required Member Function
    std::vector<Star> find(size_t n, float x, float y, float z);

    // Other Member Functions
    Node* insert(Node* ptr, Star nextStar, size_t nextDepth);
    void print() const;
};

#endif
