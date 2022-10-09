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
  fibvec.push(8);
  fibvec.push(9);
  fibvec.push(10);
  fibvec.push(11);
  //cout << "capa 1 "<< fibvec.capacity() << endl;
  fibvec.remove(5);
  fibvec.remove(5);
  fibvec.remove(4);
  fibvec.remove(3);
  fibvec.remove(2);
  fibvec.remove(1);
  // fibvec.pop();
  // fibvec.pop();
  // fibvec.pop();
  // fibvec.pop();
  // fibvec.pop();
  // fibvec.pop();
  // fibvec.pop();
  // fibvec.pop();
  // fibvec.pop();
  // cout << "\n";
  cout << "look up " << fibvec.lookup(3) << endl;
  fibvec.test();
  return 0;
}
