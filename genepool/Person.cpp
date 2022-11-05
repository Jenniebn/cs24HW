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
    if (siblings(pmod, smod).size() == 0){
        return siblings(pmod, smod);
    }
    set<Person*> newSib = siblings(pmod, smod);
    set<Person*> BROTHERS;
    for (auto maleSib : newSib){
        if (maleSib -> gender() == Gender::MALE){
            BROTHERS.insert(maleSib);
        }
    }
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
        if (grandparent -> parents(PMod::ANY).size() == 0){
            return GRANDPARENTS;
        }
        else{
            set<Person*> newGrandparent = grandparent -> parents(PMod::ANY);
            GRANDPARENTS.insert(newGrandparent.begin(), newGrandparent.end());
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
    if (parents(pmod).size() == 0){
        return parents(pmod);
    }
    set<Person*> SIBLINGS;
    set<Person*> PARENTS = parents(pmod);
    for (auto parent : PARENTS){
        if (parent -> mChildren.size() == 0){
            continue;
        }
        else if (parent -> gender() == Gender::FEMALE && pmod == PMod::MATERNAL){
            set<Person*> newSib = parent -> mChildren;
            if (smod == SMod::HALF){
                for (auto halfSib : newSib){
                    if ((halfSib -> mother() != this -> mother() && halfSib -> father() == this -> father())
                 |      (halfSib -> mother() == this -> mother() && halfSib -> father() != this -> father())){
                        SIBLINGS.insert(halfSib);
                    }
                }
                SIBLINGS.erase(this);
            }
            else{
                SIBLINGS.insert(newSib.begin(), newSib.end());
                SIBLINGS.erase(this);
            }
        }
        else if (parent -> gender() == Gender::MALE && pmod == PMod::PATERNAL){
            set<Person*> newSib = parent -> mChildren;
            if (smod == SMod::HALF){
                for (auto halfSib : newSib){
                    if ((halfSib -> mother() != this -> mother() && halfSib -> father() == this -> father())
                 |      (halfSib -> mother() == this -> mother() && halfSib -> father() != this -> father())){
                        SIBLINGS.insert(halfSib);
                    }
                }
                SIBLINGS.erase(this);
            }
            else{
                SIBLINGS.insert(newSib.begin(), newSib.end());
                SIBLINGS.erase(this);
            }
        }
        else if (pmod == PMod::ANY && smod == SMod::FULL){
            set<Person*> newSib = parent -> mChildren;
            for (auto fullSib : newSib){
                if (fullSib -> mother() == nullptr || fullSib -> father() == nullptr){
                    continue;
                }
                else if (fullSib -> mother() == this -> mother() && fullSib -> father() == this -> father()){
                    SIBLINGS.insert(fullSib);
                }
            }
            SIBLINGS.erase(this);
        }
        else if (pmod == PMod::ANY && smod == SMod::HALF){
            set<Person*> newSib = parent -> mChildren;
            for (auto halfSib : newSib){
                if ((halfSib -> mother() != this -> mother() && halfSib -> father() == this -> father())
                || (halfSib -> mother() == this -> mother() && halfSib -> father() != this -> father())){
                    SIBLINGS.insert(halfSib);
                }
            }
            SIBLINGS.erase(this);
        }
        else if (pmod == PMod::ANY && smod == SMod::ANY){
            set<Person*> newSib = parent -> mChildren;
            SIBLINGS.insert(newSib.begin(), newSib.end());
            SIBLINGS.erase(this);
        }
    }
    return SIBLINGS;
}

std::set<Person*> Person::sisters(PMod pmod, SMod smod){
    if (siblings(pmod, smod).size() == 0){
        return siblings(pmod, smod);
    }
    set<Person*> newSib = siblings(pmod, smod);
    set<Person*> SISTERS;
    for (auto femaleSib : newSib){
        if (femaleSib -> gender() == Gender::FEMALE){
            SISTERS.insert(femaleSib);
        }
    }
    return SISTERS;
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