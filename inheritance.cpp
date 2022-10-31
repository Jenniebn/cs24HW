#include <string>
#include <iostream>
#include <vector>

struct Bird{
    std::string name;
    std::string color;

    // this function with virtual means don't just use this function, but find the most up-to-date function in the subclass
    // without virtual, the function is dumb
    // as long as the parent class is virtual, the subclass is virtual
    // virtual void do_things(){ 
    //     std::cout << "Bird things...\n";
    // }

    virtual void do_things() = 0;
    // all subclasses of Bird need to do do_things, but we don't know what it can do yet
    // just this cannot make a Bird since we don't know how to do_things
    // but crow/ gull do know how to do so we can create Crow and Gull
};

struct Crow: public Bird{
    std::string color;

    void do_things(){
        std::cout << "I'm a crow!\n";
    }
};

struct Gull: public Bird{
    std::string fav_fish;
    void do_things(){
        std::cout << "I'm a gull!\n";
    }

    void swim(){
        std::cout << "The gulls swim.\n";
    }
};

// this will use what the parent has even though it does not have then function do_things itself
struct Seagull: public Gull{
    void seagull(){
        std::cout << "Mine\n";
    }
};

void print_bird(Bird* bird){
    std::cout << bird -> name << "is a bird.\n";
}


int main(){
    Bird bob;
    bob.name = "Bob";
    bob.color = "black";

    //Seagull jerry;
    Gull jerry;
    jerry.name = "Jerry";
    jerry.color = "white";

    Bird alice;
    alice.name = "Alice";

    std::vector<Bird*> birds;

    birds.push_back(&bob);
    birds.push_back(&jerry);

    //print_bird($bob);
    //bob.crow_things();

    for (size_t i = 0; i<birds.size(); ++i){
        birds[i] -> do_things();
    }

}