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

string glo = "yesy";
std::string NUM::prefix()   const{
    return glo;
}

std::string NUM::postfix()  const{
    return glo;
}

double      NUM::value()    const{
    return num;
}

// PLUS subclass
PLUS::PLUS(AST* leftNum, AST* rightNum)  {
    left = leftNum;
    right = rightNum;
}

PLUS::~PLUS() {
    delete left;
    delete right;
}

std::string PLUS::prefix()   const{
    return glo;
}

std::string PLUS::postfix()  const{
    return left -> postfix() + " " + right -> postfix() + " +";
}

double  PLUS::value()  const{
    return left -> value() + right -> value();
}


