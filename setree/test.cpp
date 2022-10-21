#include "Set.h"
#include "Node.h"
#include <iostream>

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

int main() {
  Set myset;

  myset.insert("d");
  myset.insert("b");
  myset.insert("e");
  myset.insert("a");
  myset.insert("c");
  myset.insert("f");
  cout << "original ";
  myset.print();
  myset.clear();
  // cout << myset.remove("e");
  // cout << "removed" << endl;
  // myset.remove("d");
  // cout << "removed" << endl;
  // myset.remove("c");
  // cout << "removed" << endl;
  // myset.remove("f");
  cout << "after remove ";
  myset.print();
  return 0;
}
