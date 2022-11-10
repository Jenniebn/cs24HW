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
    cout << heap.top().value << endl;
    
    heap.push("9", 9);
    heap.push("6", 6);
    heap.push("8", 8);
    heap.push("2", 2);
    

    return 0;
}
