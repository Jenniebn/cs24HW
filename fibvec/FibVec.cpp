#include <iostream> 
#include <string>
#include <algorithm>
#include "FibVec.h"
#include <stdexcept>
using namespace std;

FibVec::FibVec(){ // creates en empty vector w a capacity of one
    mCapa = 1;
    mCount = 0;
    vector = new int[mCapa];
    //cout << "constructor executed" << endl; // REMOVE
}

FibVec:: ~FibVec(){
    //cout << "destructor executed" << endl; // REMOVE
    delete [] vector;
    //delete [] newVector;
    
}

void FibVec::test(){
    for (int i = 0; i <= mCount; i++){
        cout << vector[i] << endl;
    }
}
// 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
size_t FibVec::fib(size_t n) const{
    if (n <= 1){
        return n;
    }
    return fib(n-1) + fib(n-2);
}

size_t FibVec::capacity() const{ // returns the total size of the storage buffer
    return mCapa;
}

size_t FibVec::count() const{ // returns the number of items stored in the vector
    return mCount;
}


void FibVec::resize(size_t num){
    //halfFib = fib(fibIndex - 2);
    if (num > mCapa){
        mCapa = fib(fibIndex + 1);
        fibIndex ++;
    }
    else if (num < fib(fibIndex - 2)){
    //else if (num < halfFib){
        mCapa = fib(fibIndex - 1);
        fibIndex --;
    }
}
// <_>, 1, 0
void FibVec::insert(int value, size_t index){
    size_t num = mCount + 1;
    resize(num);
    if (index > mCount){
        throw out_of_range("Out of range.");
    }
    else if (index <= mCount){
        mCount ++;
        for (size_t i = mCount - 1; i > index; i--){
            //cout << vector[index] << "old" << endl;
            vector[i + 1] = vector[i];
            //cout << vector[index] << "new" << endl;
        }
        vector[index] = value;
    }
}

int FibVec::lookup(size_t index) const{
    if (index >= mCount){
        throw out_of_range("Out of Range");
    }
    else{
        return vector[index];
    }
}

int FibVec::pop(){
    if (mCount == 0){
        throw underflow_error("Underflow Error");
    }
    else{
        mCount --;
        return vector[mCount + 1];
    }
}

void FibVec::push(int value){
    mCount ++;
    vector[mCount] = value;
}

int FibVec::remove(size_t index){
    if (index > mCount){
        throw out_of_range("Out of Range");
    }
    else{
        mCount --;
    }
    return vector[index];
}

FibVec FibVec::slice(size_t index, size_t count) const {
    (void) index;
    (void) count;
    FibVec result;
    //...
    return result;
}

