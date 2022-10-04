#include <iostream> // for cout, cin
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

class FibVec{
    public:
        FibVec();
        ~ FibVec() {};
        size_t capacity();
        size_t count();
        int insert(int value, size_t count);
        int lookup(size_t index) const;
        int pop();
        void push(int value);
        int remove(size_t index);
    private:
        vector<int> v;

};