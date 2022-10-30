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
    istringstream mystream(expression);
    string token;
    
    while(mystream >> token) {
        bool valid = ("+" || "-" || "*" || "/" || "%" || "~" || stod(token));
        // check for exceptions
        if (!valid){
            return NULL; //error messages
        }
        else{
            // link operators with numbers
            if (token == "+"){
                if (myStack.top() -> next == NULL){
                    throw runtime_error("Not enough operands.");
                }
                PLUS* plus = new PLUS(myStack.top() -> data, myStack.top() -> next -> data);
                myStack.pop();
                myStack.pop();
                myStack.push(plus);
            }
            else if (token == "-"){
                if (myStack.top() -> next == NULL){
                    throw runtime_error("Not enough operands.");
                }
                MINUS* minus = new MINUS(myStack.top() -> data, myStack.top() -> next -> data);
                myStack.pop();
                myStack.pop();
                myStack.push(minus);
            }
            else if (token == "*"){
                if (myStack.top() -> next == NULL){
                    throw runtime_error("Not enough operands.");
                }
                MULTI* multi = new MULTI(myStack.top() -> data, myStack.top() -> next -> data);
                myStack.pop();
                myStack.pop();
                myStack.push(multi);
            }
            else if (token == "/"){
                if (myStack.top() -> next == NULL){
                    throw runtime_error("Not enough operands.");
                }
                DIVIDE* divide = new DIVIDE(myStack.top() -> data, myStack.top() -> next -> data);
                myStack.pop();
                myStack.pop();
                myStack.push(divide);
            }
            else if (token == "%"){
                if (myStack.top() -> next == NULL){
                    throw runtime_error("Not enough operands.");
                }
                REMAIN* remain = new REMAIN(myStack.top() -> data, myStack.top() -> next -> data);
                myStack.pop();
                myStack.pop();
                myStack.push(remain);
            }
            else if (token == "~"){
                NEGATE* negate = new NEGATE(myStack.top() -> data);
                myStack.pop();
                myStack.push(negate);
            }

            // push the number onto stack
            else if (stod(token) || (stod(token) == 0)){
                NUM* number = new NUM(stod(token));
                myStack.push(number);
            }
        }
    }
    // check if the input line is empty
    if (myStack.head == NULL){
        throw runtime_error("No input.");
    }
    else if (myStack.top() -> next != NULL){
        throw runtime_error("Too many operands.");
    }
    return myStack.top() -> data;
}
