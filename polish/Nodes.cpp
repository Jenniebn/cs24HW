#include "Nodes.h"
#include <string>
// Implement your AST subclasses' member functions here.

// To format a double for output:
//   std::ostringstream stream;
//   stream << value;
//   return stream.str();

// NUM subclass
NUM::NUM(double newNum)  {
    num = newNum;
}

std::string NUM::prefix()   const{
    return " " + to_string(num);
}

std::string NUM::postfix()  const{
    return to_string(num) + " ";
}

double      NUM::value()    const{
    return num;
}

// PLUS subclass
PLUS::~PLUS() {
    delete left;
    delete right;
}

PLUS::PLUS(AST* leftNum, AST* rightNum)  {
    left = leftNum;
    right = rightNum;
}

double      PLUS::value()    const{
    return left -> value() + right -> value();
}

std::string PLUS::prefix()   const{
    return "+ " + left -> postfix() + " " + right -> postfix();
}

std::string PLUS::postfix()  const{
    return left -> postfix() + " " + right -> postfix() + " +";
}

// MINUS subclass
MINUS::~MINUS(){
    delete left;
    delete right;
}

MINUS::MINUS(AST* leftNum, AST* rightNum){
    left = leftNum;
    right = rightNum;
}

double      MINUS::value()   const{
    return left -> value() - right -> value();
}

std::string MINUS::prefix()   const{
    return "- " + left -> postfix() + " " + right -> postfix();
}

std::string MINUS::postfix()  const{
    return left -> postfix() + " " + right -> postfix() + " -";
}

// MULTI subclass
MULTI::~MULTI(){
    delete left;
    delete right;
}

MULTI::MULTI(AST* leftNum, AST* rightNum){
    left = leftNum;
    right = rightNum;
}

double      MULTI::value()   const{
    return left -> value() * right -> value();
}

std::string MULTI::prefix()   const{
    return "* " + left -> postfix() + " " + right -> postfix();
}

std::string MULTI::postfix()  const{
    return left -> postfix() + " " + right -> postfix() + " *";
}

// DIVIDE subclass
DIVIDE::~DIVIDE(){
    delete left;
    delete right;
}

DIVIDE::DIVIDE(AST* leftNum, AST* rightNum){
    left = leftNum;
    right = rightNum;
}

double      DIVIDE::value()   const{
    return left -> value() / right -> value();
}

std::string DIVIDE::prefix()   const{
    return "/ " + left -> postfix() + " " + right -> postfix();
}

std::string DIVIDE::postfix()  const{
    return left -> postfix() + " " + right -> postfix() + " /";
}

// REMAIN subclass
REMAIN::~REMAIN(){
    delete left;
    delete right;
}

REMAIN::REMAIN(AST* leftNum, AST* rightNum){
    left = leftNum;
    right = rightNum;
}

double      REMAIN::value()   const{
    return fmod(left -> value(), right -> value());
}

std::string REMAIN::prefix()   const{
    return "% " + left -> postfix() + " " + right -> postfix();
}

std::string REMAIN::postfix()  const{
    return left -> postfix() + " " + right -> postfix() + " %";
}

// NEGATE subclass
NEGATE::~NEGATE(){
    delete child;
}

NEGATE::NEGATE(AST* oneChild){
    child = oneChild;
}

double      NEGATE::value()   const{
    return -1 * (child -> value());
}

std::string NEGATE::prefix()   const{
    return "~ " + child -> postfix();
}

std::string NEGATE::postfix()  const{
    return child -> postfix() + " ~";
}