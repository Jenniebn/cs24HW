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
    for (int i = 0; i < mCapa; i++){
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

bool FibVec::resize(size_t num){
    //halfFib = fib(fibIndex - 2);
    if (num > mCapa){
        mCapa = fib(fibIndex + 1);
        newVector = new int[mCapa];
        fibIndex ++;
        return true;
    }
    else if (num < fib(fibIndex - 2)){
    //else if (num < halfFib){
        mCapa = fib(fibIndex - 1);
        newVector = new int[mCapa];
        fibIndex --;
        return false;
    }
}
// <_>, 1, 0
void FibVec::insert(int value, size_t index){
    if (index > mCount){
        throw out_of_range("Out of range.");
    }
    else{
        size_t num = mCount + 1;
        if (resize(num)){
            mCount ++; 
            for (size_t i = 0; i < index; i++){
                *(newVector + i) = *(vector + i);
            }
            *(newVector + index) = value;
            for (size_t j = index + 1; j < mCount; j ++){
                *(newVector + j) = *(vector + j - 1); 
            }
            delete [] vector;
            vector = newVector;
        }
        else{
            mCount ++;
            for (size_t i = mCount - 1; i > index; i --){
                *(vector + i) = *(vector + i - 1);
            }
            *(vector + index) = value;
        }
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
    remove(mCount);
    mCount --;
    return vector[mCount];
}

void FibVec::push(int value){
    insert(value, mCount);
    mCount ++;
}

int FibVec::remove(size_t index){
    if (index > mCount){
        throw out_of_range("Out of Range");
    }
    else{
        size_t num = mCount - 1;
        if (!resize(num)){
            mCount --; 
            for (size_t i = 0; i < index; i++){
                *(newVector + i) = *(vector + i);
            }
            for (size_t j = index; j < mCount; j ++){
                *(newVector + j) = *(vector + j + 1); 
            }
            delete [] vector;
            vector = newVector;
        }
        else{
            mCount --;
            temp = new int[mCapa];
            for (size_t i = 0; i < index; i++){
                *(temp + i) = *(vector + i);
            }
            for (size_t j = index; j < mCount; j ++){
                *(temp + j) = *(vector + j + 1); 
            }
            delete [] vector;
            vector = temp;
        }
    }
    return vector[index];
}


