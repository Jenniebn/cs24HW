#include "AST.h"
#include "Nodes.h"
#include "Stack.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;
using std::istringstream;

AST* AST::parse(const std::string& expression) {
    // create a stack
    stack myStack;
    // check if the input line is empty
    if (expression == ""){
        return myStack.top() -> data;
    }
    istringstream mystream(expression);
    string token;
    
    while(mystream >> token) {
        bool valid = ("+" || "-" || "*" || "/" || "%" || "~" || stod(token));
        if (!valid){
            return NULL; //error messages
        }
        else{
            // push the number onto stack
            if (stod(token)){
                NUM* number = new NUM(stod(token));
                myStack.push(number);
            }
            // link operators with numbers
            else if (token == "+"){
                PLUS* plus = new PLUS(myStack.top() -> data, myStack.top() -> next -> data);
                myStack.pop();
                myStack.pop();
                myStack.push(plus);
            }
            // else if (token == "-"){
            //     MINUS* minus = new MINUS(myStack.top() -> data, myStack.top() -> next -> data);
            //     myStack.pop();
            //     myStack.pop();
            //     myStack.push(minus);
            // }
            // else if (token == "*"){
            //     MULTI* multi = new MULTI(myStack.top() -> data, myStack.top() -> next -> data);
            //     myStack.pop();
            //     myStack.pop();
            //     myStack.push(multi);
            // }
            // else if (token == "/"){
            //     DIVIDE* divide = new DIVIDE(myStack.top() -> data, myStack.top() -> next -> data);
            //     myStack.pop();
            //     myStack.pop();
            //     myStack.push(divide);
            // }
            // else if (token == "%"){
            //     REMAIN* remain = new REMAIN(myStack.top() -> data, myStack.top() -> next -> data);
            //     myStack.pop();
            //     myStack.pop();
            //     myStack.push(remain);
            // }
            // else if (token == "~"){
            //     NEGATE* negate = new NEGATE(myStack.top() -> data);
            //     myStack.pop();
            //     myStack.push(negate);
            // }
        }
    }
    return myStack.top() -> data;
}
