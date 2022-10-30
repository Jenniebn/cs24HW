#ifndef STACK_H
#define STACK_H
#include "AST.h"

struct Node {
    AST*  data;
    Node* next;
};

class stack {
  public:
    Node* head;
    stack();
    ~stack();
    void push(AST* ptr);
    Node* pop();
    Node* top();
};
#endif
