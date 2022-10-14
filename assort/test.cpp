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
  cout << "insert" << endl;
  mylist.remove("argon");
  cout << "remove" << endl;
  //mylist.remove("helium");
  
  cout << mylist.lookup(0) << endl;
  cout << mylist.lookup(1) << endl;
  cout << "look" << endl;
  mylist.print();

  return 0;
}
