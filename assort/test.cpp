#include "List.h"
#include <iostream>
using namespace std;

// Use this file to test your List class!
// This file won't be graded - do whatever you want.

int main() {
  List mylist;
  
  mylist.insert("argon");
  mylist.insert("helium");
  mylist.insert("krypton");
  mylist.insert("neon");
  mylist.insert("oganesson");
  mylist.insert("radon");
  mylist.insert("xenon");
  size_t look = mylist.remove("argon");
  
  cout << mylist.lookup(look - 1) << endl;
  mylist.print();

  return 0;
}
