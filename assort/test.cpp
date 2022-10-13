#include "List.h"
#include <iostream>
using namespace std;

// Use this file to test your List class!
// This file won't be graded - do whatever you want.

int main() {
  List mylist;
  
  mylist.insert("A");
  mylist.insert("B");
  mylist.insert("C");
  mylist.insert("E");
  mylist.insert("B");
  mylist.insert("F");
  cout << mylist.remove("F") << endl;
  mylist.print();

  return 0;
}
