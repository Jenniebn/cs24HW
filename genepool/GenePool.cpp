#include "GenePool.h"
#include <map>
#include <iostream>
#include <sstream>
using namespace std;

// GenePool Member Functions

GenePool::GenePool(std::istream& stream){
    std::string line;
    while(std::getline(stream, line)) {
        istringstream ss(line);
        if (line == "\n" || line[0] == '#'){
                continue;
        }
        string gender, mother, father;
        getline(ss, geneName, '\t');
        getline(ss, gender, '\t');
        if (gender == "male"){
            geneGender = Gender::MALE;
        }
        else if (gender == "female"){
            geneGender = Gender::FEMALE;
        }
        getline(ss, mother, '\t');
        getline(ss, father, '\t');
        if ((mother != "???") && (father != "???")){
            geneMother = find(mother);
            geneFather = find(father);
            Person* newPerson = new Person(geneName, geneGender, geneMother, geneFather);
            family.insert(pair<string, Person*>(geneName, newPerson));
            
        }
        else if ((mother == "???") && (father != "???")){
            geneMother = nullptr;
            geneFather = find(father);
            Person* newPerson = new Person(geneName, geneGender, geneMother, geneFather);
            family.insert(pair<string, Person*>(geneName, newPerson));
        }
        else if ((mother != "???") && (father == "???")){
            geneMother = find(mother);
            geneFather = nullptr;
            Person* newPerson = new Person(geneName, geneGender, geneMother, geneFather);
            family.insert(pair<string, Person*>(geneName, newPerson));
        }
        else{
            Person* newPerson = new Person(geneName, geneGender, nullptr, nullptr);
            family.insert(pair<string, Person*>(geneName, newPerson));
        }   
        
    }
}

GenePool::~GenePool(){
    for (auto itr: family){

        delete itr.second;
        //delete itr;

    }
}

Person* GenePool::find(const std::string& name) const{
    if (family.count(name) == 0){
        return nullptr;
    }
    else{
        return family.find(name) -> second;
    }
}