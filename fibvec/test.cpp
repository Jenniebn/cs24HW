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
  fibvec.insert(4, 2);
  fibvec.insert(5, 2);
  fibvec.insert(6, 3);
  fibvec.test();
// 2 7 6 5 3 4
  return 0;
}
