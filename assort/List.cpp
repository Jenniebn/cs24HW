#include "List.h"
#include <iostream> 
#include <string>
#include <algorithm>
#include <stdexcept>
using namespace std;

List::List(){
    head = NULL;
}

List::List(const List& other){
    
}

List::List(List&& other){}
  
List::~List(){
    Node* curr = head;
    while (curr != NULL){
        Node* next = curr -> next;
        delete curr;
        curr = next;
    }
    head = NULL;
}

size_t List::count() const{}

void List::insert(const std::string& value){}

const std::string& List::lookup(size_t index) const{}

void List::print(bool reverse = false) const{
    Node* curr = head;
    if (!reverse) {
        cout << "[";
        while (curr != NULL){
            cout << curr -> data << ", ";
            curr = curr -> next;
        }
        cout << "]\n";
    }
}

std::string List::remove(size_t index){}

size_t List::remove(const std::string& value){}