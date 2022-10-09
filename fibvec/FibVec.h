#include <iostream> // for cout, cin
#include <string>
#include <algorithm>
using namespace std;

class FibVec{
    public:
        FibVec();
        ~ FibVec();
        size_t capacity() const;
        size_t count() const;
        size_t fib(size_t n) const;
        bool resize(size_t num);
        void insert(int value, size_t index);
        int lookup(size_t index) const;
        int pop();
        void push(int value);
        int remove(size_t index);
        //void test();
    private:
        size_t mCapa, mCount, fibIndex=2, halfFib;
        int* vector;
        int* newVector;
        int* temp;

};