#include "Heap.h"

Heap::Heap(size_t capacity){
    Entry* myHeap[capacity];
}

Heap::Heap(const Heap& other){

}

Heap::Heap(Heap&& other){

}

Heap::~Heap(){

}

size_t       Heap::capacity() const{
    return mCapacity;
}

size_t       Heap::count() const{
    return mCount;
}

const Heap::Entry& Heap::lookup(size_t index) const{

}

Heap::Entry        Heap::pop(){

}

Heap::Entry        Heap::pushpop(const std::string& value, float score){

}

void         Heap::push(const std::string& value, float score){

}

const Heap::Entry& Heap::top() const{

}
