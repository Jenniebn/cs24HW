#include "Nodes.h"
#include <string>
#include <cmath>
#include <sstream> 
#include <iostream>
using namespace std;
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
    std::ostringstream stream;
    stream << num;
    return stream.str();
}

std::string NUM::postfix()  const{
    std::ostringstream stream;
    stream << num;
    return stream.str();
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
    return right -> value() + left -> value();
}

std::string PLUS::prefix()   const{
    return "+ " + right -> prefix() + ' ' + left -> prefix();
}

std::string PLUS::postfix()  const{
    return right -> postfix() + ' ' + left -> postfix() + " +";
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
    return right -> value() - left -> value();
}

std::string MINUS::prefix()   const{
    return "- " + right -> prefix() + ' ' + left -> prefix();
}

std::string MINUS::postfix()  const{
    return right -> postfix() + ' ' + left -> postfix() + " -";
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
    return "* " + right -> prefix() + ' ' + left -> prefix();
}

std::string MULTI::postfix()  const{
    return right -> postfix() + ' ' + left -> postfix() + " *";
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
    if (left -> value() == 0){
        throw runtime_error("Division by zero.");
    }
    return right -> value() / left -> value();
}

std::string DIVIDE::prefix()   const{
    return "/ " + right -> prefix() + ' ' + left -> prefix();
}

std::string DIVIDE::postfix()  const{
    return right -> postfix() + ' ' + left -> postfix() + " /";
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
    if (left -> value() == 0){
        throw runtime_error("Division by zero.");
    }
    return fmod(right -> value(), left -> value());
}

std::string REMAIN::prefix()   const{
    return "% " + right -> postfix() + ' ' + left -> postfix();
}

std::string REMAIN::postfix()  const{
    return right -> postfix() + ' ' + left -> postfix() + " %";
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
    return "~ " + child -> prefix();
}

std::string NEGATE::postfix()  const{
    return child -> postfix() + " ~";
}