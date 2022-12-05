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
                STATION::EDGE newEdge(dist, transline, prePtr, mp[name]);
                //int distance, string name, STATION* pre, STATION* n
                if (trans == "BUS"){
                    newEdge.train = false;
                }
                newEdge.previous -> edge.push_back(newEdge);
                newEdge.next -> edge.push_back(newEdge);
            }
        }
        else{
            STATION* newStation = new STATION(name, num);
            if (prePtr != nullptr){
                size_t dist = newStation -> dist - prePtr -> dist;
                STATION::EDGE newEdge(dist, transline, prePtr, newStation);
                if (trans == "BUS"){
                    newEdge.train = false;
                }
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

STATION* Atlas::dijkstra(string source, string destination){
    int newDist = 0;
    string name;
    
    // push neighbors of source to heap
    Entry first(0, mp[source], ""); // first = source station where we start from
    shortToA[source] = 0; // make source distance = 0

    for(auto edge: first.station -> edge) {
        if (edge.next != first.station){
            Entry newEntry(edge.dist, edge.next, edge.lineName);
            shortToA[edge.next -> statName] = edge.dist;
            myHeap.push(newEntry);
            edge.next -> previous = first.station;
            edge.next -> lineName = edge.lineName;
        }
        else{
            Entry newEntry(edge.dist, edge.previous, edge.lineName);
            shortToA[edge.previous -> statName] = edge.dist;
            myHeap.push(newEntry);
            edge.previous -> previous = first.station;
            edge.previous -> lineName = edge.lineName;
        }
    }
    unvisited[source] = false;
    // loop through the graph and find shortest path from source to destination
    
    while (myHeap.size() > 0){
        Entry curr = myHeap.top();
        //cout << curr -> station -> statName << endl;
        myHeap.pop();
        
        if (curr.station -> statName == destination){
            return curr.station;
        }
        // if the station is not visited yet
        if (unvisited[curr.station -> statName] == true){
            for(auto edge: curr.station -> edge) {
                newDist = curr.dist + edge.dist;
                // if the neighbor is not visited yet and distance is smaller
                if (edge.next == curr.station){
                    if ((unvisited[edge.previous -> statName] == true) && (newDist < shortToA[edge.previous -> statName])){
                        Entry nextEntry(newDist, edge.previous, edge.lineName);
                        shortToA[edge.previous -> statName] = newDist;
                        myHeap.push(nextEntry);
                        edge.previous -> previous = curr.station;
                        edge.previous -> lineName = edge.lineName;
                    }
                }
                else {
                    if ((unvisited[edge.next -> statName] == true) && (newDist < shortToA[edge.next -> statName])){
                        Entry nextEntry(newDist, edge.next, edge.lineName);
                        shortToA[edge.next -> statName] = newDist;
                        myHeap.push(nextEntry);
                        edge.next -> previous = curr.station;
                        edge.next -> lineName = edge.lineName;
                    }
                }
            }
        }
        unvisited[curr.station -> statName] = false;
    }
    return nullptr;
}

Atlas::~Atlas(){
    for(std::map<std::string, STATION*>::iterator itr = mp.begin(); itr != mp.end(); itr++){
        delete itr -> second;
    }
}

Trip Atlas::route(const std::string& src, const std::string& dst){
    STATION* curr = dijkstra(src, dst);
    //cout << curr -> statName << endl;
    for (auto [k, v]: unvisited){
        unvisited[k] = true;
    }
    if (curr == nullptr){
        throw runtime_error("No route.");
    }
    Trip bestTrip;
    bestTrip.start = src;
    Trip::Leg newLeg;
    newLeg.line = curr -> lineName;
    newLeg.stop = curr -> statName;
    bestTrip.legs.push_back(newLeg);
    string oldLine = curr -> lineName;
    curr = curr -> previous;
    while (curr -> previous != nullptr){
        //cout << curr -> statName << endl;
        if ((curr -> statName != src) && (oldLine != curr -> lineName)){
            newLeg.line = curr -> lineName;
            newLeg.stop = curr -> statName;
            bestTrip.legs.push_back(newLeg);
            oldLine = curr -> lineName;
        }
        curr = curr -> previous;
    }
    reverse(bestTrip.legs.begin(), bestTrip.legs.end());
    return bestTrip;
}