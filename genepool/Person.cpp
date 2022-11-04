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
        if (ancestor -> mother() != nullptr && ancestor -> father() != nullptr){
            set<Person*> newAncestors = ancestor -> ancestors(PMod::ANY);
            ANCESTORS.insert(newAncestors.begin(), newAncestors.end());
        }
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
    if (mChildren.size() == 0){
        return mChildren;
    }
    set<Person*> DESCENDANTS = mChildren;
    for (auto descendant : DESCENDANTS){
        set<Person*> newDescestors = descendant -> descendants();
        DESCENDANTS.insert(newDescestors.begin(), newDescestors.end());
    }
    return DESCENDANTS;
}

std::set<Person*> Person::grandchildren(){
    if (mChildren.size() == 0){
        return mChildren;
    }
    set<Person*> GRANDCHILDREN;
    for (auto grandchild : mChildren){
        set<Person*> newGrandchild = grandchild -> mChildren;
        GRANDCHILDREN.insert(newGrandchild.begin(), newGrandchild.end());
    }
    return GRANDCHILDREN;
}

std::set<Person*> Person::granddaughters(){
    if (mChildren.size() == 0){
        return mChildren;
    }
    set<Person*> old = grandchildren();
    set<Person*> GRANDDAUGHTERS;
    for (auto granddaughter : old){
        if (granddaughter -> gender() == Gender::FEMALE){
            GRANDDAUGHTERS.insert(granddaughter);
        }
    }
    return GRANDDAUGHTERS;
}
std::set<Person*> Person::grandfathers(PMod pmod){
    if (grandparents(pmod).size() == 0){
        return grandparents(pmod);
    }
    set<Person*> old = grandparents(pmod);
    set<Person*> GRANDFATHERS;
    for (auto grandfather : old){
        if (grandfather -> gender() == Gender::MALE){
            GRANDFATHERS.insert(grandfather);
        }
    }
    return GRANDFATHERS;
}
std::set<Person*> Person::grandmothers(PMod pmod){
    if (grandparents(pmod).size() == 0){
        return grandparents(pmod);
    }
    set<Person*> old = grandparents(pmod);
    set<Person*> GRANDMOTHERS;
    for (auto grandmother : old){
        if (grandmother -> gender() == Gender::FEMALE){
            GRANDMOTHERS.insert(grandmother);
        }
    }
    return GRANDMOTHERS;
}
std::set<Person*> Person::grandparents(PMod pmod){
    if (parents(pmod).size() == 0){
        return parents(pmod);
    }
    set<Person*> GRANDPARENTS;
    for (auto grandparent : parents(pmod)){
        if (grandparent -> parents(pmod).size() == 0){
            return GRANDPARENTS;
        }
        else if (grandparent -> mother() != nullptr && grandparent -> father() != nullptr){
            GRANDPARENTS.insert(grandparent -> mMother);
            GRANDPARENTS.insert(grandparent -> mFather);
        }
        else if (grandparent -> mother() == nullptr && grandparent -> father() != nullptr){
            GRANDPARENTS.insert(grandparent -> mFather);
        }
        else if (grandparent -> mother() != nullptr && grandparent -> father() == nullptr){
            GRANDPARENTS.insert(grandparent -> mMother);
        }
    }
    return GRANDPARENTS;
}
std::set<Person*> Person::grandsons(){
    if (mChildren.size() == 0){
        return mChildren;
    }
    set<Person*> old = grandchildren();
    set<Person*> GRANDSONS;
    for (auto grandson : old){
        if (grandson -> gender() == Gender::MALE){
            GRANDSONS.insert(grandson);
        }
    }
    return GRANDSONS;
}
std::set<Person*> Person::nephews(PMod pmod, SMod smod){
    return set<Person*>();
}
std::set<Person*> Person::nieces(PMod pmod, SMod smod){
    return set<Person*>();
}

std::set<Person*> Person::parents(PMod pmod){
    set<Person*> PARENTS;
    if (pmod == PMod::MATERNAL && mMother != nullptr){
        PARENTS.insert(mMother);
    }
    else if (pmod == PMod::PATERNAL && mFather != nullptr){
        PARENTS.insert(mFather);
    }
    else if (pmod == PMod::ANY && mMother != nullptr && mFather == nullptr){
        PARENTS.insert(mMother);
    }
    else if (pmod == PMod::ANY && mMother == nullptr && mFather != nullptr){
        PARENTS.insert(mFather);
    }
    else if (pmod == PMod::ANY && mMother != nullptr && mFather != nullptr){
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