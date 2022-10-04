#include <iostream> // for cout, cin
#include <string>
#include <algorithm>
#include "FibVec.h"
#include <vector>
#include <stdexcept>
using namespace std;

FibVec::FibVec(){
    vector<int> v;
    cout << "constructor executed" << endl;
}

int FibVec::capacity(){
    return v.capacity();
}

int main( )
{
    FibVec num;
    

    
    return 0;
}
