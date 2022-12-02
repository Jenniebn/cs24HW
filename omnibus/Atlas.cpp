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
        cout << name << endl;
        // check if the station is in the map already
        if (mp.count(name) >0){ 
            size_t dist = prePtr -> dist - mp[name] -> dist;
            STATION::EDGE* newEdge = nullptr;
            newEdge -> lineName = transline;
            newEdge -> dist = dist;
            if (trans == "BUS"){
                newEdge -> train = false;
            }
            newEdge -> previous = prePtr;
            newEdge -> next = mp[name];
            mp[name] -> edge.push_back(newEdge);
            prePtr -> edge.push_back(newEdge);
        }
        else{
            STATION* newStation = new STATION(name, num);
            if (prePtr != nullptr){
                cout << "before\n";
                size_t dist = newStation -> dist - prePtr -> dist;
                STATION::EDGE* newEdge = nullptr;
                newEdge -> lineName = transline;
                newEdge -> dist = dist;
                
                if (trans == "BUS"){
                    newEdge -> train = false;
                }
                newEdge -> previous = prePtr;
                newEdge -> next = newStation;
                newStation -> edge.push_back(newEdge);
                prePtr -> edge.push_back(newEdge);
                cout << "after9\n";
            }
            cout << "after0\n";
            mp.insert({name, newStation});
            cout << "after1\n";
            unvisited.insert(newStation);
            cout << "after2\n";
            shortToA.insert({name, INT_MAX});
            cout << "after3\n";
            
        }
        
        prePtr = mp[name];
    }
}

bool compare(pair<string, int> i, pair<string, int> j){
    return i.second < j.second;
}

void Atlas::dijkstra(map<string, STATION*> graph, string source, string destination){
    // make the source distance 0
    shortToA[source] = 0;
    int newDist = 0;
    string name;
    
    // push neighbors of source to heap
    Entry* first = nullptr;
    first -> dist = 0;
    first -> station = graph[source];
    first -> previous = nullptr;
    Entry* newStat = nullptr;
    for(auto edge: first -> station -> edge) {
        newStat -> dist = edge -> dist;
        newStat -> station = edge -> next;
        newStat -> previous = first;
        newStat -> lineName = edge -> lineName;
        myHeap.push(newStat);
    }
    visited.insert(first -> station);
    // loop through the graph and find shortest path from source to destination
    while (unvisited.size() != 0){
        // pair<string, int> min = *min_element(shortToA.begin(), shortToA.end(), compare);
        // name = min.first; // name == the station name with the smallest known distance from start station
        Entry* curr;
        curr = myHeap.top();
        myHeap.pop();
        if (curr -> station -> statName == destination){
            bestRoute.insert(curr);
            break;
        }
        // if the station is not visited yet
        if (visited.find(curr -> station) != visited.end()){
            for(auto edge: curr -> station -> edge) {
                newDist = curr -> dist + edge -> dist;
                // if the neighbor is not visited yet and distance is smaller
                if ((visited.find(edge -> next) != visited.end()) && (newDist < shortToA[edge -> next -> statName])){
                    shortToA[edge -> next -> statName] = newDist;
                    newStat -> dist = newDist;
                    newStat -> previous = curr;
                    newStat -> station = edge -> next;
                    newStat -> lineName = edge -> lineName;
                    myHeap.push(newStat);
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
    
    dijkstra(mp, src, dst);
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