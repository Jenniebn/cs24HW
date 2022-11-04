#include "Person.h"
#include <iostream>
using namespace std;

// Person Member Functions

const std::string& Person::name()   const{
    return mName;
}

Gender             Person::gender() const{
    return mGender;
}

Person*            Person::mother(){
    return mMother;
}

Person*            Person::father(){
    return mFather;
}

set<Person*>  Person::newChildren(){
    return mChildren;
}

Person::Person(const std::string name, Gender gender, Person* mother, Person* father){
    mName   = name;
    mGender = gender;
    mMother = mother;
    mFather = father;
    if (mother != nullptr && father != nullptr){
        mMother -> mChildren.insert(this);
        mFather -> mChildren.insert(this);
    }
    else if (mother == nullptr && father != nullptr){
        mFather -> mChildren.insert(this);
    }
    else if (mother != nullptr && father == nullptr){
        mMother -> mChildren.insert(this);
    }
}

Person::~Person(){
    // delete mMother;
    // delete mFather;
}

std::set<Person*> Person::ancestors(PMod pmod){
    set<Person*> ANCESTORS = parents(pmod);
    for (auto ancestor: ANCESTORS){
        ANCESTORS.insert(ancestor -> mother());
        ANCESTORS.insert(ancestor -> father());
    }
    return ANCESTORS;
}

std::set<Person*> Person::aunts(PMod pmod, SMod smod){
    set<Person*> AUNTS;
    return AUNTS;
}

std::set<Person*> Person::brothers(PMod pmod, SMod smod){
    set<Person*> BROTHERS;
    return BROTHERS;
}

std::set<Person*> Person::children(){
    return mChildren;
}

std::set<Person*> Person::cousins(PMod pmod, SMod smod) {
	set<Person*> COUSINS;
	// set<Person*> parentSibs = parentSiblings(pmod, smod);
	// for (auto parentSib : parentSibs) {
    //     set<Person*> allCousins = parentSib -> children();
	// 	cousins.insert(allCousins.begin(), allCousins.end());
	// }
	return COUSINS;
}

std::set<Person*> Person::daughters(){
    set<Person*> DAUGHTERS;
    if (children().empty()){
        return DAUGHTERS;
    }
    for (auto fChildren : children()){
        if (fChildren -> gender() == Gender::FEMALE){
            DAUGHTERS.insert(fChildren);
        }
    }
    return DAUGHTERS;
}
std::set<Person*> Person::descendants(){
    return set<Person*>();
}
std::set<Person*> Person::grandchildren(){
    return set<Person*>();
}
std::set<Person*> Person::granddaughters(){
    return set<Person*>();
}
std::set<Person*> Person::grandfathers(PMod pmod){
    set<Person*> GRANDFATHERS = grandparents(pmod);
    return GRANDFATHERS;
}
std::set<Person*> Person::grandmothers(PMod pmod){
    set<Person*> GRANDMOTHERS = grandparents(pmod);
    return GRANDMOTHERS;
}
std::set<Person*> Person::grandparents(PMod pmod){
    set<Person*> GRANDPARENTS;
    for (auto grandparent : parents(pmod)){
        bool grandmaExist = grandparent -> mMother != nullptr;
        bool grandpaExist = grandparent -> mFather != nullptr;
        if (pmod == PMod::ANY && !grandmaExist && !grandpaExist){
            continue;
        }
        else if (pmod == PMod::MATERNAL && grandmaExist){
            GRANDPARENTS.insert(grandparent -> mMother);
        }
        else if (pmod == PMod::PATERNAL && grandpaExist){
            GRANDPARENTS.insert(grandparent -> mFather);
        }
        else if (pmod == PMod::ANY && grandmaExist && grandpaExist){
            GRANDPARENTS.insert(grandparent -> mMother);
            GRANDPARENTS.insert(grandparent -> mFather);
        }
        else if (pmod == PMod::ANY && !grandmaExist && grandpaExist){
            GRANDPARENTS.insert(grandparent -> mFather);
        }
        else if (pmod == PMod::ANY && grandmaExist && !grandpaExist){
            GRANDPARENTS.insert(grandparent -> mMother);
        }
    }
    return GRANDPARENTS;
}
std::set<Person*> Person::grandsons(){
    return set<Person*>();
}
std::set<Person*> Person::nephews(PMod pmod, SMod smod){
    return set<Person*>();
}
std::set<Person*> Person::nieces(PMod pmod, SMod smod){
    return set<Person*>();
}

std::set<Person*> Person::parents(PMod pmod){
    set<Person*> PARENTS;
    if (pmod == PMod::MATERNAL){
        PARENTS.insert(mMother);
    }
    else if (pmod == PMod::PATERNAL){
        PARENTS.insert(mFather);
    }
    else if (pmod == PMod::ANY){
        PARENTS.insert(mMother);
        PARENTS.insert(mFather);
    }
    return PARENTS;
}

std::set<Person*> Person::siblings(PMod pmod, SMod smod){
    return set<Person*>();
}
std::set<Person*> Person::sisters(PMod pmod, SMod smod){
    return set<Person*>();
}

std::set<Person*> Person::sons(){
    set<Person*> SONS;
    if (children().empty()){
        return SONS;
    }
    for (auto mChildren : children()){
        if (mChildren -> gender() == Gender::MALE){
            SONS.insert(mChildren);
        }
    }
    return SONS;
}

std::set<Person*> Person::uncles(PMod pmod, SMod smod){
    return set<Person*>();
}