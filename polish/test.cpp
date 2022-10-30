#include "AST.h"
#include "Stack.h"
#include "Nodes.h"
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

// If you want a different main function, write it here!
// This file won't be graded - do whatever you want.
// void printTree(AST* ptr);
// void printTree(AST* ptr){
//     if (ptr == NULL) {
//         return;
//     }
//     bool has_children = (ptr->left != NULL || ptr->right != NULL);
//     if (has_children){
//         printTree(ptr -> left);
//         cout << " ";
//     }
//     cout << ptr -> data;
//     if (has_children){
//         cout << " ";
//         printTree(ptr -> right);
//     }
// }

int main() {
  // string line;
  // AST* ast = NULL;
  // while(getline(cin, line)) {
  //     ast = AST::parse(line);
  // }
  // cout << ast -> value() << endl;

  size_t check = 0;
  istringstream mystream("+");
  string token;
  
  while(mystream >> token) {
    stod(token, &check);
    cout << token << endl;
    cout << check << endl;
  }
  


  return 0;
}
