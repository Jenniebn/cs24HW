#include <cstddef>

class FibVec{
    public:
        FibVec();
        ~ FibVec() {delete [] v;};
        size_t capacity();
        size_t count();
        int insert(int value, size_t count);
        int lookup(size_t index) const;
        int pop();
        void push(int value);
        int remove(size_t index);
        

};