
#include "AST.h"
#include "Nodes.h"
#include "Stack.h"
#include <iostream>
#include <sstream>
#include <string>
#include <ctype.h>
using namespace std;
using std::istringstream;
// check if the token is valid or not
bool validToken(string myToken){
    // if the token is one of the operators return true
    if ((myToken == "+" || "-" || "*" || "/" || "%" || "~") && (myToken.length() == 1)){
        return true;
    }
    // check for invalid token all characters e.g. "one"
    for (size_t i = 0; i < myToken.length(); i++){
        if ((myToken[i] == '-') || (myToken[i] == '+')){
            continue;
        }
        else if (myToken[i] == '.'){
            continue;
        }
        if (!isdigit(myToken[i])){
            throw runtime_error("Invalid token: " + myToken);
            return false;
        }
    }
    // check for invalid token all characters e.g. "2ab"
    size_t check = 0;
    stod(myToken, &check);
    if (check != myToken.length()){
        throw runtime_error("Invalid token: " + myToken);
        return false;
    }
    return false;
}

AST* AST::parse(const std::string& expression) {
    // create a stack
    stack myStack;
    istringstream mystream(expression);
    string token;

    while(mystream >> token) {
        validToken(token);
        size_t stackSize = myStack.stackSize();
        // link operators with numbers
        if (token == "+"){
            if (stackSize < 2){
                throw runtime_error("Not enough operands.");
            }
            PLUS* plus = new PLUS(myStack.top() -> data, myStack.top() -> next -> data);
            myStack.pop();
            myStack.pop();
            myStack.push(plus);
        }
        else if (token == "-"){
            if (stackSize < 2){
                throw runtime_error("Not enough operands.");
            }
            MINUS* minus = new MINUS(myStack.top() -> data, myStack.top() -> next -> data);
            myStack.pop();
            myStack.pop();
            myStack.push(minus);
        }
        else if (token == "*"){
            if (stackSize < 2){
                throw runtime_error("Not enough operands.");
            }
            MULTI* multi = new MULTI(myStack.top() -> data, myStack.top() -> next -> data);
            myStack.pop();
            myStack.pop();
            myStack.push(multi);
        }
        else if (token == "/"){
            if (stackSize < 2){
                throw runtime_error("Not enough operands.");
            }
            DIVIDE* divide = new DIVIDE(myStack.top() -> data, myStack.top() -> next -> data);
            myStack.pop();
            myStack.pop();
            myStack.push(divide);
        }
        else if (token == "%"){
            if (stackSize < 2){
                throw runtime_error("Not enough operands.");
            }
            REMAIN* remain = new REMAIN(myStack.top() -> data, myStack.top() -> next -> data);
            myStack.pop();
            myStack.pop();
            myStack.push(remain);
        }
        else if (token == "~"){
            if (stackSize < 1){
                throw runtime_error("Not enough operands.");
            }
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
    // check if the input line is empty
    if (myStack.head == NULL){
        throw runtime_error("No input.");
    }
    else if (myStack.top() -> next != NULL){
        throw runtime_error("Too many operands.");
    }
    AST* lastNode = myStack.top() -> data;
    myStack.pop();
    return lastNode;
}