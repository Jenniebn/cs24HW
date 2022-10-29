#ifndef NODES_H
#define NODES_H
#include <string>
#include "AST.h"
using namespace std;

// Declare your AST subclasses here.
// Implement their member functions in Nodes.cpp.
// AST* ast = AST::parse(line);

class NUM: public AST{
    public:
        NUM(double newNum);
        std::string prefix()  const;
        std::string postfix() const;
        double      value()   const;
    private:
        double num;
};

class PLUS: public AST{
    public:
        string op = "+";
        PLUS(AST* leftNum, AST* rightNum);
        ~PLUS();
        std::string prefix()  const;
        std::string postfix() const;
        double      value()   const;
    private: 
        AST* left;
        AST* right;
};

class MINUS: public AST{
    public:
        string op = "-";
        MINUS(AST* leftNum, AST* rightNum);
        ~MINUS();
        std::string prefix()  const;
        std::string postfix() const;
        double      value()   const;
    private: 
        AST* left;
        AST* right;
};

class MULTI: public AST{
    public:
        string op = "*";
        MULTI(AST* leftNum, AST* rightNum);
        ~MULTI();
        std::string prefix()  const;
        std::string postfix() const;
        double      value()   const;
    private: 
        AST* left;
        AST* right;
};

class DIVIDE: public AST{
    public:
        string op = "/";
        DIVIDE(AST* leftNum, AST* rightNum);
        ~DIVIDE();
        std::string prefix()  const;
        std::string postfix() const;
        double      value()   const;
    private: 
        AST* left;
        AST* right;
};

class REMAIN: public AST{
    public:
        string op = "%";
        REMAIN(AST* leftNum, AST* rightNum);
        ~REMAIN();
        std::string prefix()  const;
        std::string postfix() const;
        double      value()   const;
    private: 
        AST* left;
        AST* right;
};

class NEGATE: public AST{
    public:
        string op = "~";
        NEGATE(AST* oneChild);
        ~NEGATE();
        std::string prefix()  const;
        std::string postfix() const;
        double      value()   const;
    private:
        AST* child;
};

#endif
