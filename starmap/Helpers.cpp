#include "Helpers.h"

// Space to implement helper class member functions.
#include "Helpers.h"

Node::Node(){
    right = NULL;
    left = NULL;
}

Node::Node(Star value){
    data = value;
    right = NULL;
    left = NULL;
}

Node:: ~Node(){
    delete left;
    delete right;
}