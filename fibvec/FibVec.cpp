#include <iostream> // for cout, cin
#include <string>
#include <algorithm>
#include "FibVec.h"
#include <vector>
#include <stdexcept>
using namespace std;

FibVec::FibVec(){ // creates en empty vector w a capacity of one
    mCount = 1;
    vector = new int[mCount];
    cout << "constructor executed" << endl; // REMOVE
}

FibVec:: ~FibVec(){
    cout << "destructor executed" << endl; // REMOVE
    delete [] vector;
}

size_t FibVec::capacity() const{ // returns the total size of the storage buffer
    return mCount;
}

size_t FibVec::count() const{ // returns the number of items stored in the vector
    return mCount;
}

void FibVec::insert(int value, size_t index){
    (void) value;
    (void) index;
    // size_t countNum = count();
    // if (index > countNum){
    //     throw out_of_range("Out of range.");
    // }
    // else if (){
        
    // }
}

int FibVec::lookup(size_t index) const{
    (void) index;
    return vector[index];
}

int FibVec::pop(){
    return mCount;
}

void FibVec::push(int value){
    (void) value;
}

int FibVec::remove(size_t index){
    (void) index;
    return mCount;
}

FibVec FibVec::slice(size_t index, size_t count){
    (void) index;
    (void) count;
    FibVec result;
    //...
    return result;
}

// int main( )
// {
//     FibVec num;
    

    
//     return 0;
// }
