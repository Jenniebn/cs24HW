#include "Set.h"
#include "Node.h"
#include <iostream>

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

int main() {
  Set myset;

  myset.insert("10");
  myset.insert("5");
  myset.insert("3");
  myset.insert("6");
  myset.insert("14");
  myset.insert("12");
  myset.insert("17");
  cout << "original ";
  myset.print();
  
  myset.remove("12");
  cout << "removed" << endl;
  myset.remove("6");
  cout << "removed" << endl;
  myset.remove("3");
  cout << "removed" << endl;
  //myset.remove("17");
  //myset.remove("10");
  cout << "after remove ";
  myset.print();
  cout << "print" << endl;
  return 0;
}
