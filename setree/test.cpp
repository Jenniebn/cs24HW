#include "Set.h"
#include "Node.h"
#include <iostream>

// Use this file to test your Set class.
// This file won't be graded - do whatever you want.

int main() {
  Set myset;
  myset.insert("Britches");
  
  myset.insert("ANDi");
  myset.insert("Betsy");
  myset.insert("Able");
  myset.insert("Albert");
  myset.insert("Baker");
  myset.insert("Boo");
  myset.insert("Binx");
  myset.insert("Jack");
  
  myset.insert("Crystal");
  myset.insert("Hellion");
  myset.insert("Gordo");
  myset.insert("Jacco");
  myset.insert("Finster");
  myset.insert("Govi");
  myset.insert("Fred");
  myset.insert("Semos");
  myset.insert("Maggie");
  myset.insert("Loon");
  myset.insert("Sam");
  myset.insert("Ramu");
  myset.insert("Tetra");
  myset.print();
  myset.remove("Betsy");
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
