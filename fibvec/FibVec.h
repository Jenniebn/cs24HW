#include <iostream> // for cout, cin
#include <string>
#include <algorithm>
using namespace std;

class FibVec{
    public:
        FibVec();
        ~ FibVec() {};
        size_t capacity() const;
        size_t count() const;
        void insert(int value, size_t index);
        int lookup(size_t index) const;
        int pop();
        void push(int value);
        int remove(size_t index);
        FibVec slice(size_t index, size_t count);
    private:
        int mCount;
        int* vector;

};