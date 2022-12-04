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
            continue;
        }
        istringstream ss(line); //convert line into a stream for reading
        
        size_t num = 0;
        ss >> temp; // temp = BUS/TRAIN
        // store BUS/ TRAIN
        if (temp != "-"){
            prePtr = nullptr;
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
            unvisited.insert(newStation);
            shortToA.insert({name, INT_MAX});
        }
        prePtr = mp[name];
    }
}

void Atlas::dijkstra(string source, string destination){
    // make the source distance 0
    shortToA[source] = 0;
    int newDist = 0;
    string name;
    
    // push neighbors of source to heap
    Entry* first = new Entry;
    first -> dist = 0;  
    first -> station = mp[source];  // first = source station where we start from
    first -> previous = nullptr;
    Entry* newEntry = new Entry;
    for(auto edge: first -> station -> edge) {
        newEntry -> dist = edge -> dist;
        newEntry -> station = edge -> next;
        newEntry -> previous = first;
        newEntry -> lineName = edge -> lineName;
        myHeap.push(newEntry);
    }
    visited.insert(first -> station);
    unvisited.erase(first -> station);
    // loop through the graph and find shortest path from source to destination
    while (unvisited.size() != 0){
        Entry* curr = new Entry;
        curr = myHeap.top();
        myHeap.pop();
        if (curr -> station -> statName == destination){
            bestRoute.insert(curr);
            break;
        }
        // if the station is not visited yet
        if (!(visited.find(curr -> station) != visited.end())){
            for(auto edge: curr -> station -> edge) {
                newDist = curr -> dist + edge -> dist;
                // cout << curr -> station -> statName << endl;
                // cout << newDist << endl;
                // if the neighbor is not visited yet and distance is smaller
                if (!(visited.find(edge -> next) != visited.end()) && (newDist < shortToA[edge -> next -> statName])){
                    shortToA[edge -> next -> statName] = newDist;
                    newEntry -> dist = newDist;
                    newEntry -> previous = curr;
                    newEntry -> station = edge -> next;
                    newEntry -> lineName = edge -> lineName;
                    myHeap.push(newEntry);
                }
            }
            visited.insert(curr -> station);
            unvisited.erase(curr -> station);
        }
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