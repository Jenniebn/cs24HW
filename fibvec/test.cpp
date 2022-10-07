#include "FibVec.h"
#include <iostream> 
#include <string>
#include <algorithm>
#include <stdexcept>
using namespace std;

// Use this file to test your FibVec class!
// This file won't be graded - do whatever you want.

int main() {
  FibVec fibvec;
  fibvec.insert(2, 0);
  fibvec.insert(3, 1);
  cout << fibvec.lookup(1) << endl;
  fibvec.insert(4, 1);
  cout << fibvec.lookup(1) << endl;
  fibvec.insert(5, 1);
  cout << fibvec.lookup(1) << endl;
  fibvec.insert(6, 1);
  cout << fibvec.lookup(1) << endl;
  fibvec.insert(7, 1);
  cout << fibvec.lookup(1) << endl;
  fibvec.test();

  return 0;
}
