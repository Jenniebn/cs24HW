#include "Node.h"

Node::Node(){
    right = NULL;
    left = NULL;
}

Node::Node(string value){
    data = value;
    right = NULL;
    left = NULL;
}

Node:: ~Node(){
    delete left;
    delete right;
}