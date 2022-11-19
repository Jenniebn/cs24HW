#include "Helpers.h"

// Space to implement helper class member functions.
#include "Helpers.h"

Node::Node(){
    right = nullptr;
    left = nullptr;
}

Node::Node(Star value){
    data = value;
    right = nullptr;
    left = nullptr;
}

Node:: ~Node(){
    delete left;
    delete right;
}