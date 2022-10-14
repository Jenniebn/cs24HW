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
    // if (other == NULL){
    //     head = other;
    // }
    // else{
    //     head = new Node{ other.head -> data, other.head -> next};
    //     Node* tocopy = other.head -> next;
    //     Node* curr = head;
    //     while (curr != N){
    //         curr -> next = new Node {tocopy.data, tocopy -> next};
    //         tocopy = tocopy -> next;
    //         curr = curr -> next;
    //     }
    // }
}

List::List(List&& other){
    head = other.head;
    other.head = NULL;
}
  
List::~List(){
    Node* curr = head;
    while (curr != NULL){
        Node* next = curr -> next;
        delete curr;
        curr = next;
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
}

string returnValue = "";
const std::string& List::lookup(size_t index) const{
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

std::string List::remove(size_t index){
    size_t num = count();
    Node* curr = head;
    Node* oldNode = new Node;
    if (index >= num){
        throw out_of_range("Out of Range");
    }
    else if (num == 1){
        oldNode = head;
        returnValue += oldNode -> data;
        head = NULL;
        return returnValue;
    }
    else if (index == 0){
        oldNode = head;
        returnValue += oldNode -> data;
        head = curr -> next;
        curr = NULL;
        return returnValue;
    }
    else if (index == num - 1){
        for (size_t i = 0; i < num - 2; i++){
            curr = curr -> next;
        }
        oldNode = curr -> next;
        returnValue += oldNode -> data;
        curr -> next = NULL;
        return returnValue;
    }
    else{
        for (size_t j = 0; j < index - 1; j++){
            curr = curr -> next;
        }
        oldNode = curr -> next;
        returnValue += oldNode -> data;
        curr -> next = oldNode -> next;
        oldNode = NULL;
        return returnValue;
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