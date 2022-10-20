#ifndef NODE_H
#define NODE_H
#include <string>
using namespace std;

// Use this file to declare your Node type.
// Implement Node member functions and helper functions in Node.cpp.

class Node{
  public:
    size_t count = 0;
    string data;
    Node* left;
    Node* right;
    Node(string value);
};

#endif
