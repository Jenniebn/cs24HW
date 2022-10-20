#include "Node.h"

Node::Node(string value){
    data = value;
    right = NULL;
    left = NULL;
}

Node:: ~Node(){
    delete left;
    delete right;
}