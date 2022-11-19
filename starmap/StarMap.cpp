#include "StarMap.h"
#include "Helpers.h"
#include <iostream>
#include <sstream>
#include <string>
#include <queue>  
#include <vector> 
#include <cmath> 
#include <math.h>  
#include <algorithm>
using namespace std;

StarMap* StarMap::create(std::istream& stream) {
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new StarMap(stream); // this calls the constructor
}


StarMap::StarMap(std::istream& stream){
    std::string line;
    while(std::getline(stream, line)) {
        istringstream ss(line);
        string temp;
        float xAxis, yAxis, zAxis;
        
        
        getline(ss, temp, '\t');
        xAxis = stof(temp);
        getline(ss, temp, '\t');
        yAxis = stof(temp);
        getline(ss, temp, '\t');
        zAxis = stof(temp);
        Star newStar;
        newStar.id = index;
        newStar.x = xAxis;
        newStar.y = yAxis;
        newStar.z = zAxis;
        tree = insert(tree, newStar, depth);
        index++;
    }
} 

Node* StarMap::insert(Node* ptr, Star nextStar, size_t nextDepth){
  if (ptr == nullptr){
    return new Node(nextStar);
  }
  size_t dim = nextDepth % 3;
  if (((dim == 0) && (nextStar.x >= ptr -> data.x)) || ((dim == 1) && (nextStar.y >= ptr -> data.y)) || ((dim == 2) && (nextStar.z >= ptr -> data.z))){
    ptr -> right = insert(ptr -> right, nextStar, nextDepth + 1);
  }
  else {
    ptr -> left = insert(ptr -> left, nextStar, nextDepth + 1);
  }
  return ptr;
}

StarMap::~StarMap(){
  delete tree;
  tree = nullptr;
}

void findNeighbor(size_t num, size_t depth, Star target, Node* root, priority_queue<Entry>& queue){
  if (root == nullptr){
    return;
  }

  Entry newEntry;
  newEntry.score = sqrt((root -> data.x - target.x) * (root -> data.x - target.x) + (root -> data.y - target.y) * (root -> data.y - target.y) + (root -> data.z - target.z) * (root -> data.z - target.z));
  newEntry.star = root -> data;
  
  size_t dim = depth % 3; 
  
  if (queue.size() < num){
    queue.push(newEntry);
  }
  else if ((queue.size() >= num) && (newEntry.score < queue.top().score)){
    queue.pop();
    queue.push(newEntry);
  }
  
  // going down
  Node* nextBranch = nullptr;
  Node* otherBranch = nullptr;
  if (((dim == 0) && (target.x >= root -> data.x)) || ((dim == 1) && (target.y >= root -> data.y)) || ((dim == 2) && (target.z >= root -> data.z))){
    nextBranch = root -> right;
    otherBranch = root -> left;
  }
  else{
    nextBranch = root -> left;
    otherBranch = root -> right;
  }
  
  findNeighbor(num, depth + 1, target, nextBranch, queue);
  
  // going backup
  if (dim == 0){
    newEntry.boundary = abs(target.x - root -> data.x);
  }
  if (dim == 1){
    newEntry.boundary = abs(target.y - root -> data.y);
  }
  if (dim == 2){
    newEntry.boundary = abs(target.z - root -> data.z);
  }
  if (queue.top().score > newEntry.boundary){
    findNeighbor(num, depth + 1, target, otherBranch, queue);
  }
}

std::vector<Star> StarMap::find(size_t n, float x, float y, float z){ 
  Star newStar;
  newStar.id = index;
  newStar.x = x;
  newStar.y = y;
  newStar.z = z;
  Node* curr = tree;
  findNeighbor(n, depth, newStar, curr, myQueue);
  vector<Star> nearNeighbor;
  while (! myQueue.empty() ){
    Entry temp = myQueue.top();
    nearNeighbor.push_back(temp.star);
    myQueue.pop();
  }
  reverse(nearNeighbor.begin(), nearNeighbor.end());
  return nearNeighbor;
}


void printTree(Node* ptr){
  if (ptr == NULL) {
        cout << "-";
        return;
    }
    bool has_children = (ptr->left != NULL || ptr->right != NULL);
    if (has_children){
        cout << "(";
        printTree(ptr -> left);
        cout << " ";
    }
    cout << " x: " << ptr -> data.x << "y: " << ptr -> data.y << "z: " << ptr -> data.z;
    if (has_children){
        cout << " ";
        printTree(ptr -> right);
        cout << ")";
    }
}

void StarMap::print() const{
    Node* curr = tree;
    if (curr == NULL){
        cout << "nothing"; 
    }
    else{
        printTree(curr);
    }
    cout << endl;
}