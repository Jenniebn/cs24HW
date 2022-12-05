#include "Atlas.h"
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <map>
#include <utility> 
#include <vector>
#include <algorithm> 
#include <limits.h>
using namespace std;

Atlas* Atlas::create(std::istream& stream) {
  // This default implementation will probably do what you want.
  // If you use a different constructor, you'll need to change it.
  return new Atlas(stream);
}

Atlas::Atlas(std::istream& stream){
    std::string line;
    string trans, transline, temp, name, numS;
    while(std::getline(stream, line)) { // read each line from the file
        if ((line.length() == 0) || (line[0] == '#')){
            prePtr = nullptr;
            continue;
        }
        istringstream ss(line); //convert line into a stream for reading
        
        size_t num = 0;
        ss >> temp; // temp = BUS/TRAIN
        // store BUS/ TRAIN
        if (temp != "-"){
            trans = temp.substr(0, temp.size() - 1); // delete :
            ss >> std:: ws;
            getline(ss, transline); // transline == line name e.g. Line 15X
            continue;
        }
        else if (temp == "-"){
            ss >> numS;
            if (trans == "TRAIN"){
                num = stoi(numS); // TRAIN station all not have time 0
            }
            ss >> std:: ws;
            getline(ss, name); // name == station name
        }
        // check if the station is in the map already
        if (mp.count(name) > 0){ 
            if (prePtr != nullptr){
                size_t dist = mp[name] -> dist - prePtr -> dist;
                STATION::EDGE* newEdge = new STATION::EDGE(dist, transline);
                if (trans == "BUS"){
                    newEdge -> train = false;
                }
                newEdge -> previous = prePtr;
                newEdge -> next = mp[name];
                newEdge -> previous -> edge.push_back(newEdge);
                newEdge -> next -> edge.push_back(newEdge);
            }
        }
        else{
            STATION* newStation = new STATION(name, num);
            if (prePtr != nullptr){
                size_t dist = newStation -> dist - prePtr -> dist;
                STATION::EDGE* newEdge = new STATION::EDGE(dist, transline);
                if (trans == "BUS"){
                    newEdge -> train = false;
                }
                newEdge -> previous = prePtr;
                newEdge -> next = newStation;
                newEdge -> previous -> edge.push_back(newEdge);
                newEdge -> next -> edge.push_back(newEdge);
            }
            mp.insert({name, newStation});
            unvisited.insert({name, true});
            shortToA.insert({name, INT_MAX});
        }
        prePtr = mp[name];
    }
}

void Atlas::dijkstra(string source, string destination){
    int newDist = 0;
    string name;
    
    // push neighbors of source to heap
    Entry* first = new Entry;
    shortToA[source] = 0; // make source distance = 0
    first -> dist = 0;  
    first -> station = mp[source];  // first = source station where we start from
    first -> previous = nullptr;
    Entry* newEntry = new Entry;
    for(auto edge: first -> station -> edge) {
        newEntry -> dist = edge -> dist;
        newEntry -> station = edge -> next;
        newEntry -> previous = first;
        newEntry -> lineName = edge -> lineName;
        shortToA[edge -> next -> statName] = edge -> dist;
        myHeap.push(newEntry);
    }
    unvisited[source] = false;
    // cout << "from source " << first -> station -> statName << endl;
    // loop through the graph and find shortest path from source to destination
    Entry* curr = new Entry;
    //int i =0;
    
    while (myHeap.size() > 0){
        curr = myHeap.top();
        myHeap.pop();
        if (curr -> station -> statName == destination){
            bestRoute.insert(curr);
            break;
        }
        // if the station is not visited yet
        if (unvisited[curr -> station -> statName] == true){
            for(auto edge: curr -> station -> edge) {
                newDist = curr -> dist + edge -> dist;
                // if the neighbor is not visited yet and distance is smaller
                if ((unvisited[edge -> next -> statName] == true) && (newDist < shortToA[edge -> next -> statName])){
                    Entry* nextEntry = new Entry;
                    shortToA[edge -> next -> statName] = newDist;
                    nextEntry -> dist = newDist;
                    nextEntry -> previous = curr;
                    nextEntry -> station = edge -> next;
                    nextEntry -> lineName = edge -> lineName;
                    myHeap.push(nextEntry);
                }
            }
        }
        unvisited[curr -> station -> statName] = false;
    }
}

Atlas::~Atlas(){
    delete prePtr;
}

Trip Atlas::route(const std::string& src, const std::string& dst){
    dijkstra(src, dst);
    if (bestRoute.empty()){
        throw runtime_error("No route.");
    }
    Trip bestTrip;
    bestTrip.start = src;
    Entry* curr = myHeap.top();
    Trip::Leg newLeg;
    newLeg.line = curr -> lineName;
    newLeg.stop = curr -> station -> statName;
    bestTrip.legs.push_back(newLeg);
    curr = curr -> previous;
    while (curr -> previous != nullptr){
        if (curr -> station -> statName != src){
            newLeg.line = curr -> lineName;
            newLeg.stop = curr -> station -> statName;
            bestTrip.legs.push_back(newLeg);
            curr = curr -> previous;
        }
    }
    reverse(bestTrip.legs.begin(), bestTrip.legs.end());
    return bestTrip;
}