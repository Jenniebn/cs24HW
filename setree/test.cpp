#include "Set.h"
#include "Node.h"
#include <iostream>

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

int main() {
  Set myset;
  myset.insert("m");
  
  myset.insert("f");
  myset.insert("a");
  myset.insert("p");
  myset.insert("m");
  myset.insert("n");
  myset.insert("q");
  
  myset.print();
  myset.remove("p");
  // cout << "lookup "<<myset.lookup(21) << endl;
  //myset.print();
  // cout << "original ";
  // myset.print();
  // cout << myset.remove("a") << endl;
  // myset.print();
  // cout << myset.remove("c") << endl;
  // myset.print();
  // cout << myset.remove("z") << endl;
  // myset.print();
  // myset.remove("e");
  cout << "after remove ";
  myset.print();
  // Set newlist(myset);
  // newlist.print();
  return 0;
}
