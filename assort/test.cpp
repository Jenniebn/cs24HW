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
  mylist.remove("argon");
  mylist.remove("krypton");
  mylist.remove("oganesson");
  cout << "remove" << endl;
  mylist.remove("xenon");
  cout << "remove" << endl;
  mylist.remove("helium");
  cout << "remove" << endl;
  cout << "mylist ";
  mylist.print();
  List newlist(mylist);
  cout << "newlist ";
  newlist.print();

  return 0;
}
