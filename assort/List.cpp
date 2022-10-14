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
    if (other.head == NULL){
        head = other.head;
    }
    else{
        head = new Node;
        head -> data = other.head -> data;
        head -> next = other.head -> next;
        Node* tocopy = other.head -> next;
        Node* curr = head;
        while (curr != NULL){
            curr -> data = tocopy -> data;
            curr -> next = tocopy -> next;
            tocopy = tocopy -> next;
            curr = curr -> next;
        }
    }
}

List::List(List&& other){
    head = other.head;
    other.head = NULL;
}
  
List::~List(){
    Node* curr = head;
    while (curr != NULL){
        Node* next = curr;
        curr = curr -> next;
        delete next;
    }
    head = NULL;
}

size_t List::count() const{
    size_t count = 0;
    Node* curr = head;
    while (curr != nullptr){
        ++ count;
        curr = curr -> next;
    }
    return count;
} 


void List::insert(const std::string& value){
    Node* curr = head;
    Node* newNode = new Node;
    newNode -> data = value;
    if (head == NULL){
        head =newNode;
        newNode -> next = NULL;
    }
    else if (newNode -> data < head -> data){
        newNode -> next = head;
        head = newNode;
    }
    else{
        while (true){
            if ((curr -> next == NULL) || (curr -> next -> data > newNode -> data)){
                newNode -> next = curr -> next;
                curr -> next = newNode;
                break;
            }
            curr = curr -> next;
        }
    }
    delete newNode;
}

string returnValue = "";
const std::string& List::lookup(size_t index) const{
    returnValue = "";
    size_t n = count();
    size_t i = 0;
    Node* curr = head;
    if (index >= n){
        throw out_of_range("Out of Range");
    }
    else if (index == 0){
        returnValue += head -> data;
        return returnValue;
    }
    else{
        while (curr != NULL){
            if (i == index){
                returnValue += curr -> data;
                return returnValue;
            }
            curr = curr -> next;
            i++;
        }
    }
    return returnValue;
}

void List::print(bool reverse) const{
    Node* curr = head;
    size_t n = count();
    size_t index = n;
    if (n == 0){
        cout << "[]\n";
    }
    else if (!reverse) {
        cout << "[";
        size_t i = 0;
        while (curr != nullptr){
            if (i < n - 1){
                cout << curr -> data << ", ";
                curr = curr -> next;
            }
            else{
                cout << curr -> data << "]\n";
                break;
            }
            i ++;
        }
    }
    else{
        cout << "[";
        size_t currNum = index - 1;
        size_t zero = 0;
        while (currNum >= zero){
            for (size_t j = 1; j < index; j++){
                curr = curr -> next;
            }
            if (currNum != zero){
                cout << curr -> data << ", ";
            }
            else{
                cout << curr -> data << "]\n";
                break;
            }
            curr = head;
            currNum --;
            index --;
        }
    }
}

string removeValue = "";
std::string List::remove(size_t index){
    removeValue = "";
    size_t num = count();
    Node* curr = head;
    Node* oldNode = new Node;
    if (index >= num){
        delete curr;
        delete oldNode;
        throw out_of_range("Out of Range");
    }
    else if (num == 1){
        oldNode = head;
        removeValue += oldNode -> data;
        head = NULL;
        delete curr;
        delete oldNode;
        return removeValue;
    }
    else if (index == 0){
        oldNode = head;
        removeValue += oldNode -> data;
        head = curr -> next;
        curr = NULL;
        delete curr;
        delete oldNode;
        return removeValue;
    }
    else if (index == num - 1){
        for (size_t i = 0; i < num - 2; i++){
            curr = curr -> next;
        }
        oldNode = curr -> next;
        removeValue += oldNode -> data;
        curr -> next = NULL;
        delete curr;
        delete oldNode;
        return removeValue;
    }
    else{
        for (size_t j = 0; j < index - 1; j++){
            curr = curr -> next;
        }
        oldNode = curr -> next;
        removeValue += oldNode -> data;
        curr -> next = oldNode -> next;
        oldNode = NULL;
        delete curr;
        delete oldNode;
        return removeValue;
    }
}

size_t List::remove(const std::string& value){
    size_t num = count();
    size_t total = 0;
    Node* curr = head;
    while (curr != NULL){
        for (size_t i = 0; i < num; i++){
            if (curr -> data == value){
                remove(i);
                total ++;
                num = count();
                curr = head;
                break;
            }
            curr = curr -> next;
        }
    }
    return total;
}