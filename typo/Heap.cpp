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
    mCount = other.count();
    mCapacity = other.capacity();
    for (size_t i = 0; i < other.count(); i++){
        mData[i] = other.mData[i];
    }
}

Heap::Heap(Heap&& other){
    mCount = other.count();
    mCapacity = other.capacity();
    mData = other.mData;
    other.mData = NULL;
    other.mCount = 0;
    other.mCapacity = 0;
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
    size_t zero = 0;
    // std::cout << "index = " << index << std::endl;
    // std::cout << "count() = " << count() << std::endl;
    if ((index > count() - 1) || (index < zero)){
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
                    continue;
                }
                else if (mData[leftChild].score < mData[index].score){
                    Heap::Entry temp = mData[leftChild];
                    mData[leftChild] = mData[index];
                    mData[index] = temp;
                    index = leftChild;
                    continue;
                }
            }
            else if ((leftChild < count()) && (mData[leftChild].score < mData[index].score)){
                Heap::Entry temp = mData[leftChild];
                mData[leftChild] = mData[index];
                mData[index] = temp;
                index = leftChild;
                continue;
            }
            break;
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
                if ((mData[leftChild].score > mData[rightChild].score) && (mData[rightChild].score < mData[index].score)){
                    Heap::Entry temp = mData[rightChild];
                    mData[rightChild] = mData[index];
                    mData[index] = temp;
                    index = rightChild;
                    continue;
                }
                else if (mData[leftChild].score < mData[index].score){
                    Heap::Entry temp = mData[leftChild];
                    mData[leftChild] = mData[index];
                    mData[index] = temp;
                    index = leftChild;
                    continue;
                }
            }
            else if ((leftChild < count()) && (mData[leftChild].score < mData[index].score)){
                Heap::Entry temp = mData[leftChild];
                mData[leftChild] = mData[index];
                mData[index] = temp;
                index = leftChild;
                continue;
            }
            break;
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
