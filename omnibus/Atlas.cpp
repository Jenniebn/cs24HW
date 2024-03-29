#include <queue> 
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
            trans = temp.substr(0, temp.size() - 1); // delete :
            ss >> std:: ws;
            getline(ss, transline); // transline == line name e.g. Line 15X
            prePtr = nullptr;
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
        //cout << "name " << name << endl;
        // check if the station is in the map already
        if (mp.count(name) > 0){ 
            mp[name] -> dist = num;
            if (prePtr != nullptr){
                size_t dist = mp[name] -> dist - prePtr -> dist;
                //std::cout <<  mp[name] -> dist << " " << prePtr -> dist << '\n';
                STATION::EDGE newEdge(dist, transline, prePtr, mp[name]);
                //int distance, string name, STATION* pre, STATION* n
                if (trans == "BUS"){
                    newEdge.train = false;
                }
                newEdge.previous -> edge.push_back(newEdge);
                newEdge.next -> edge.push_back(newEdge);
                // cout << "old " << newEdge.previous -> statName << " <-> " << newEdge.next -> statName << " dist " << dist << endl;
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
                //cout << "new " << newEdge.previous -> statName << " <-> " << newEdge.next -> statName << " dist " << dist << endl;
            }
            mp.insert({name, newStation});
            unvisited.insert({newStation, true});
            shortToA.insert({newStation, INT_MAX});
        }
        prePtr = mp[name];
    }
}

STATION* Atlas::dijkstra(string source, string destination){
    int newDist = 0;
    string name;
    
    // push neighbors of source to heap
    Entry first(0, mp[source], ""); // first = source station where we start from
    shortToA[mp[source]] = 0; // make source distance = 0
    myHeap.push(first);
    
    while (myHeap.size() > 0){
        Entry curr = myHeap.top();
        //cout << curr -> station -> statName << endl;
        myHeap.pop();
        
        if (curr.station -> statName == destination){
            return curr.station;
        }
        // if the station is not visited yet
        // cout << "curr station " << curr.station -> statName << " dist" << shortToA[curr.station -> statName] << endl;
        if (unvisited[curr.station] == true){
            for(auto edge: curr.station -> edge) {
                newDist = curr.dist + edge.dist;
                STATION* next;
                if (edge.next == curr.station){
                    next = edge.previous;
                }
                else {
                    next = edge.next;
                }
                // if the neighbor is not visited yet and distance is smaller
                if ((unvisited[next] == true) && (newDist < shortToA[next])){
                    // std::cout << newDist << " to " << next->statName << '\n';
                    Entry nextEntry(newDist, next, edge.lineName);
                    shortToA[next] = newDist;
                    myHeap.push(nextEntry);
                    next -> previous = curr.station;
                    next -> lineName = edge.lineName;
                }

            }
        }
        unvisited[curr.station] = false;
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
    
    while (curr -> previous != nullptr){
        //cout << curr -> statName << endl;
        curr = curr -> previous;
        if ((curr -> statName != src) && (oldLine != curr -> lineName)){
            newLeg.line = curr -> lineName;
            newLeg.stop = curr -> statName;
            bestTrip.legs.push_back(newLeg);
            oldLine = curr -> lineName;
        }
    }
    reverse(bestTrip.legs.begin(), bestTrip.legs.end());
    for (auto [k, v]: unvisited){
        unvisited[k] = true;
    }
    for (auto [a, b]: shortToA){
        shortToA[a] = INT_MAX;
    }
    for (auto [i, j]: mp){
        mp[i] -> previous = nullptr;
    }
    myHeap = priority_queue<Entry>();
    return bestTrip;
}