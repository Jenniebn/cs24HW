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
                STATION::EDGE newEdge;
                newEdge.dist = dist;
                newEdge.lineName = transline;
                if (trans == "BUS"){
                    newEdge.train = false;
                }
                newEdge.previous = prePtr;
                newEdge.next = mp[name];
                newEdge.previous -> edge.push_back(newEdge);
                newEdge.next -> edge.push_back(newEdge);
            }
        }
        else{
            STATION* newStation = new STATION(name, num);
            if (prePtr != nullptr){
                size_t dist = newStation -> dist - prePtr -> dist;
                STATION::EDGE newEdge;
                newEdge.dist = dist;
                newEdge.lineName = transline;
                if (trans == "BUS"){
                    newEdge.train = false;
                }
                newEdge.previous = prePtr;
                newEdge.next = newStation;
                newEdge.previous -> edge.push_back(newEdge);
                newEdge.next -> edge.push_back(newEdge);
            }
            mp.insert({name, newStation});
            unvisited.insert({name, true});
            shortToA.insert({name, INT_MAX});
        }
        prePtr = mp[name];
    }
}

Entry* Atlas::dijkstra(string source, string destination){
    int newDist = 0;
    string name;
    
    // push neighbors of source to heap
    Entry* first = new Entry(0, mp[source], nullptr, ""); // first = source station where we start from
    shortToA[source] = 0; // make source distance = 0

    for(auto edge: first -> station -> edge) {
        if (edge.next != first -> station){
            Entry* newEntry = new Entry(edge.dist, edge.next, first, edge.lineName);
            shortToA[edge.next -> statName] = edge.dist;
            myHeap.push(newEntry);
        }
        else{
            Entry* newEntry = new Entry(edge.dist, edge.previous, first, edge.lineName);
            shortToA[edge.previous -> statName] = edge.dist;
            myHeap.push(newEntry);
        }
    }
    unvisited[source] = false;
    // loop through the graph and find shortest path from source to destination
    
    while (myHeap.size() > 0){
        Entry* curr = myHeap.top();
        myHeap.pop();
        if (curr -> station -> statName == destination){
            return curr;
        }
        // if the station is not visited yet
        if (unvisited[curr -> station -> statName] == true){
            for(auto edge: curr -> station -> edge) {
                newDist = curr -> dist + edge.dist;
                // if the neighbor is not visited yet and distance is smaller
                if (edge.next == curr -> station){
                    if ((unvisited[edge.previous -> statName] == true) && (newDist < shortToA[edge.previous -> statName])){
                        Entry* nextEntry = new Entry(newDist, edge.previous, curr, edge.lineName);
                        shortToA[edge.previous -> statName] = newDist;
                        myHeap.push(nextEntry);
                    }
                }
                else {
                    if ((unvisited[edge.next -> statName] == true) && (newDist < shortToA[edge.next -> statName])){
                        Entry* nextEntry = new Entry(newDist, edge.next, curr, edge.lineName);
                        shortToA[edge.next -> statName] = newDist;
                        myHeap.push(nextEntry);
                    }
                }
            }
        }
        unvisited[curr -> station -> statName] = false;
    }
    return nullptr;
}

Atlas::~Atlas(){
    for(std::map<std::string, STATION*>::iterator itr = mp.begin(); itr != mp.end(); itr++){
        delete itr -> second;
    }
}

Trip Atlas::route(const std::string& src, const std::string& dst){
    Entry* curr = dijkstra(src, dst);
    if (curr == nullptr){
        throw runtime_error("No route.");
    }
    Trip bestTrip;
    bestTrip.start = src;
    Trip::Leg newLeg;
    newLeg.line = curr -> lineName;
    newLeg.stop = curr -> station -> statName;
    bestTrip.legs.push_back(newLeg);
    string oldLine = curr -> lineName;
    curr = curr -> previous;
    
    while (curr -> previous != nullptr){
        if ((curr -> station -> statName != src) && (oldLine != curr -> lineName)){
            newLeg.line = curr -> lineName;
            newLeg.stop = curr -> station -> statName;
            bestTrip.legs.push_back(newLeg);
            oldLine = curr -> lineName;
        }
        curr = curr -> previous;
    }
    reverse(bestTrip.legs.begin(), bestTrip.legs.end());
    return bestTrip;
}