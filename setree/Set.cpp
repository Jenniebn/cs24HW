#include "Set.h"
#include "Node.h"
#include <string>
#include <iostream> 
using namespace std;

Set::Set(){
    mRoot = NULL;
}

Set::Set(const Set& other){
    
}

Set::Set(Set&& other){
    mRoot = other.mRoot;
    other.mRoot = NULL;
}

Set::~Set(){
    delete mRoot;
}

size_t Set::clear(){
    size_t removed = count();
    if (removed == 0){
        return 0;
    }
    else {
        delete mRoot;
        mRoot = nullptr;
        return removed;
    }
}

bool containTree(Node* ptr, const std::string& value){
    if (ptr == NULL)
        return false;
    if (ptr -> data == value)
        return true;
    
    bool existL = containTree(ptr -> left, value);
    
    if (existL){
        return true;
    } 
 
    bool existR = containTree(ptr -> right, value);
    return existR;
}

bool Set::contains(const std::string& value) const{
    Node* curr = mRoot;
    return containTree(curr, value);
}

size_t countTree(const Node* ptr){
    if (ptr == nullptr){
        return 0;
    }
    else {
        return countTree(ptr -> left) + countTree(ptr -> right) + 1;
    }
}

size_t Set::count() const{
    Node* curr = mRoot;
    return countTree(curr);
}

void Set::debug(){}

size_t insertNode(Node* ptr, const std::string& value){
    if (ptr -> data == value){
        return 0;
    }
    if (value > ptr -> data){
        if (ptr -> right == NULL){
            ptr -> right = new Node(value);
            return 1;
        }
        else {
            return insertNode(ptr -> right, value);
        }
    }
    if (value < ptr -> data) {
        if (ptr -> left == NULL){
            ptr -> left = new Node(value);
            return 1;
        }
        else{
            return insertNode(ptr -> left, value);
        }
    }
    return 0;
}

size_t Set::insert(const std::string& value){
    Node* curr = mRoot;
    if (mRoot == NULL){
        mRoot = new Node(value); 
        return 1;
    }
    else {
        return insertNode(curr, value);
    }
}

std::string yes = "yes";
const std::string& Set::lookup(size_t n) const{
    n += 1;
    return yes;
}

void printTree(Node* ptr){
    if (ptr == NULL) {
        cout << "-";
        return;
    }
    bool has_children = (ptr->left != NULL || ptr->right != NULL);
    if (has_children){
        cout << "(";
        printTree(ptr -> left);
        cout << " ";
    }
    cout << ptr -> data;
    if (has_children){
        cout << " ";
        printTree(ptr -> right);
        cout << ")";
    }
}

void Set::print() const{
    Node* curr = mRoot;
    if (curr == nullptr){
        cout << endl;
    }
    else{
        printTree(curr);
    }
    cout << endl;
}

Node* locatePre(const std::string& value, Node* ptr){
    if (value > ptr -> data){
        if (ptr -> right -> data == value){
            return ptr;
        }
        return locatePre(value, ptr -> right);
    }
    else {
        if (ptr -> left -> data == value){
            return ptr;
        }
        return locatePre(value, ptr -> left);
    }
}

Node* locateCurr(const std::string& value, Node* ptr){
    if (value > ptr -> data){
        if (ptr -> data == value){
            return ptr;
        }
        return locateCurr(value, ptr -> right);
    }
    else {
        if (ptr -> data == value){
            return ptr;
        }
        return locateCurr(value, ptr -> left);
    }
}

void removeLeaf(Node* pre, Node* curr, bool L, bool R){
    delete curr;
    if(L && !R){
        pre -> left = NULL;
    }
    else {
        pre -> right = NULL;
    }
}

void remove1Par(Node* pre, Node* curr){
    bool nextL = curr -> left;
    bool nextR = curr -> right;
    bool preNextL = (pre -> left == curr);
    bool preNextR = (pre -> right == curr);
    if (preNextL && nextL){
        pre -> left = curr -> left;
        delete curr;
    }
    else if (preNextL && nextR){
        pre -> left = curr -> right;
        delete curr;
    }
    else if (preNextR && nextL){
        pre -> right = curr -> left;
        delete curr;
    }
    else if (preNextR && nextR){
        pre -> right = curr -> right;
        delete curr;
    }
}

void removePar(Node* curr){
    Node* swap = curr -> right;
    
    //cout << "curr data " << curr -> data << endl;
    while (swap -> left != NULL){
        swap = swap -> left;
    }
    // cout << "swap data " << swap -> data << endl;
    // cout << swap -> data << endl;
    // string temp = swap -> data;
    // cout << temp << endl;
    // curr -> data = temp;
    // delete swap -> left;
    // swap -> left = NULL;
}


size_t Set::remove(const std::string& value){
    Node* curr = mRoot;
    if (contains(value) == false){
        return 0;
    }
    if (mRoot -> data == value){
        delete mRoot;
        mRoot = nullptr;
        return 1;
    }
    Node* pre = locatePre(value, curr);
    curr = locateCurr(value, curr);
    
    // cout << "pre value " << pre -> data << endl;
    // cout << "curr value " << curr -> data << endl;
    
    bool has0Children = ((curr -> left == NULL) && (curr -> right == NULL));
    bool has2Children = ((curr -> left != NULL) && (curr -> right != NULL));
    
    if (has0Children){
        if (pre -> right == curr){
            removeLeaf(pre, curr, false, true);
            return 1;
        }
        else{
            removeLeaf(pre, curr, true, false);
            return 1;
        }
    }
    else if (has2Children){
        removePar(curr);
        return 1;
    }
    else{
        remove1Par(pre, curr);
        return 1;
    }
    return 1;
}
