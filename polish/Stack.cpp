#include "Stack.h"
using namespace std;
#include <iostream>
// Implement your Stack member functions here.

stack::stack(){
    head = NULL;
}

stack::~stack(){
    // delete head;
    // head = NULL;
    Node* curr = head;
    while (curr != NULL){
        Node* next = curr -> next;
        delete curr -> data;
        //curr -> data = nullptr;
        delete curr;
        curr = next;
    }
    head = NULL;
}

void stack::push(AST* ptr){
    Node* newNode = new Node;
    newNode -> data = ptr;
    // ptr = NULL;
    newNode -> next = NULL;
    if (head == NULL){
        head = newNode;
    }
    else{
        newNode -> next = head;
        head = newNode;

    }
}
    
Node* stack::pop(){
    if (head == NULL){
        return NULL;
    }
    else{
        Node* temp = head;
        head = temp -> next;
        // delete temp -> data;
        delete temp;
        //temp -> data = nullptr;
        temp = NULL;
        return head;
    }
}
    
Node* stack::top(){
    if (head != NULL){
        return head;
    }
    else{
        return NULL;
    }
}

size_t stack::stackSize(){
    size_t count = 0;
    Node* curr = head;
    while (curr != nullptr){
        ++ count;
        curr = curr -> next;
    }
    return count;
}