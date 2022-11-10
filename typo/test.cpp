#include "Heap.h"
#include <iostream>
using namespace std;

// Use this file to test your Heap class!
// This file won't be graded - do whatever you want.

int main() {
    Heap heap(8);
    heap.push("5", 5);
    heap.push("3", 3);
    heap.push("1", 1);
    
    
    heap.push("9", 9);
    heap.push("6", 6);
    heap.push("8", 8);
    heap.pop();
    heap.push("2", 2);
   

    for (size_t i = 0; i < heap.count(); i++){
        cout << heap.lookup(i).value << endl;
    }

    return 0;
}
