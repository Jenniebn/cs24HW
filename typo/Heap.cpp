#include "Heap.h"
#include <iostream> 
using namespace std;

Heap::Heap(size_t capacity){
    mCount = 0;
    mCapacity = capacity;
    mData = new Heap::Entry[capacity];
}

Heap::Heap(const Heap& other){
    mData = new Heap::Entry[other.capacity()];
    for (size_t i = 0; i < other.count(); i++){
        mData[i] = other.mData[i];
    }
}

Heap::Heap(Heap&& other){
    mData = other.mData;
    other.mData = NULL;
}

Heap::~Heap(){
    delete [] mData; 
}

size_t       Heap::capacity() const{
    return mCapacity;
}

size_t       Heap::count() const{
    return mCount;
}

const Heap::Entry& Heap::lookup(size_t index) const{
    if (index > count() - 1){
        throw out_of_range("Out of Range");
    }
    else{
        return mData[index];
    }
}

Heap::Entry        Heap::pop(){
    if (count() == 0){
        throw underflow_error("Underflow Error");
    }
    else{
        Heap::Entry lowest = mData[0];
        Heap::Entry last = mData[count() - 1];
        mData[0] = last;
        mCount --;
        size_t index = 0;
        size_t leftChild = index * 2 + 1;
        size_t rightChild = index * 2 + 2;
        while (index < count()){
            leftChild = index * 2 + 1;
            rightChild = index * 2 + 2;
            if (leftChild < count() && rightChild < count()){
                if ((mData[leftChild].score > mData[rightChild].score) && (mData[rightChild].score < mData[index].score)){
                    Heap::Entry temp = mData[rightChild];
                    mData[rightChild] = mData[index];
                    mData[index] = temp;
                    index = rightChild;
                }
                else if (mData[leftChild].score < mData[index].score){
                    Heap::Entry temp = mData[leftChild];
                    mData[leftChild] = mData[index];
                    mData[index] = temp;
                    index = leftChild;
                }
            }
            else if (mData[leftChild].score < mData[index].score){
                Heap::Entry temp = mData[leftChild];
                mData[leftChild] = mData[index];
                mData[index] = temp;
                index = leftChild;
            }
            else{
                break;
            }
        }
        return lowest;
    }
}

Heap::Entry        Heap::pushpop(const std::string& value, float score){
     if (count() == 0){
        throw underflow_error("Underflow Error");
    }
    else{
        Heap::Entry lowest = mData[0];
        Heap::Entry newEntry;
        newEntry.value = value;
        newEntry.score = score;
        mData[0] = newEntry;
        size_t index = 0;
        size_t leftChild = index * 2 + 1;
        size_t rightChild = index * 2 + 2;
        while (index < count()){
            leftChild = index * 2 + 1;
            rightChild = index * 2 + 2;
            if (leftChild < count() && rightChild < count()){
                if (mData[leftChild].score > mData[rightChild].score){
                    Heap::Entry temp = mData[rightChild];
                    mData[rightChild] = mData[index];
                    mData[index] = temp;
                    index = rightChild;
                }
            }
            else{
                Heap::Entry temp = mData[leftChild];
                mData[leftChild] = mData[index];
                mData[index] = temp;
                index = leftChild;
            }
        }
        return lowest;
    }
}

void         Heap::push(const std::string& value, float score){
    if (count() >= capacity()){
        throw overflow_error("Overflow Error");
    }
    Heap::Entry newEntry;
    newEntry.value = value;
    newEntry.score = score;
    
    mData[count()] = newEntry;
    
    size_t index = count();
    mCount++;
    size_t zero = 0;
    while(index >= zero){
        size_t parent = (index - 1) / 2;
        if (mData[parent].score <= mData[index].score){
            break;
        }
        else{
            Heap::Entry temp = mData[parent];
            mData[parent] = mData[index];
            mData[index] = temp;
            index = parent;
        }
    }
}

const Heap::Entry& Heap::top() const{
    if (count() == 0){
        throw underflow_error("Underflow Error");
    }
    else{
        return mData[0];
    }
}
