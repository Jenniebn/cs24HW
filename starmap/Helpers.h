#ifndef HELPERS_H
#define HELPERS_H
#include <string>
#include "Star.h"
using namespace std;

// If you want to add any helper classes,
// here's some space to do it in.

class Node{
  public:
    Star data;
    Node* left;
    Node* right;

    Node();
    Node(Star value);
    ~Node();
};

struct Entry {
    float score;
    float boundary = 0;
    Star star;

    bool operator < (const Entry& other) const { // pointer to the tree which is priority queue, each element in the tree is entry type
        return this->score < other.score;
    }
};


#endif
