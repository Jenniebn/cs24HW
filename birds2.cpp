#include <iostream>
#include <vector>

struct Bird {
    // hidden member: vtable
    std::string type;
    std::string name;
    std::string color;
    int         born;

    Bird(
        std::string type,
        std::string name,
        std::string color,
        int born
    ) {
        this->type  = type;
        this->name  = name;
        this->color = color;
        this->born  = born;
    }

    int age() const {
        int current_year = 2022; // function call!
        return current_year - born;
    }

    virtual std::string diet() const = 0;

    void describe() const {
        std::cout
            << name  << " is a " << age() << "-year-old "
            << color << " " << type << ".\n";
    }

    void feed() const {
        std::cout << "You feed " << name << " some " << diet() << ".\n";
    }
};

struct Crow: public Bird {
    Crow(std::string name, int born): Bird("crow", name, "black", born) {
        // All done!
    }

    std::string diet() const {
        return "bugs";
    }
};

struct Parrot: public Bird {
    // std::string color;

    Parrot(std::string name, int born, std::string color):
        Bird("parrot", name, color, born)
    {
        // this->color = color;
    }

    std::string diet() const {
        return "seeds";
    }
};

struct AfricanGreyParrot: public Parrot {
    AfricanGreyParrot(std::string name, int born): Parrot(name, born, "grey") {
        // All done!
    }

    void describe() const {
        std::cout << name << " is an African Grey Parrot.\n";
    }

    void speak_french() {
        std::cout << "Oui oui!\n";
    }
};

void feed_the_birds(const std::vector<Bird*>& birds) {
    for(size_t i = 0; i < birds.size(); ++i) {
        Bird* bird = birds[i];
        bird->feed();
    }
}

void list_the_birds(const std::vector<Bird*>& birds) {
    for(size_t i = 0; i < birds.size(); ++i) {
        Bird* bird = birds[i];
        bird->describe();
    }
}

int main() {
    Crow amy("Amy",   2020);
    Crow bob("Bob",   2017);
    Crow carl("Carl", 2019);
    Crow dave("Dave", 2014);
    Crow fred("Fred", 2017);

    Parrot polly("Polly",  2010, "blue");
    Parrot sammy("Sammy",  2016, "red");

    // Bird bartholemew("???", "Bartholemew", "brownish", 2022);

    AfricanGreyParrot arthur("Arthur", 1972);

    std::vector<Bird*> birds;
    birds.push_back(&amy);
    birds.push_back(&bob);
    birds.push_back(&carl);
    birds.push_back(&dave);
    birds.push_back(&fred);

    birds.push_back(&polly);
    birds.push_back(&sammy);

    // birds.push_back(&bartholemew);

    birds.push_back(&arthur);

    // amy.describe();
    // bob.describe();
    // carl.describe();

    // polly.describe();
    // sammy.describe();

    list_the_birds(birds);
    std::cout << '\n';
    feed_the_birds(birds);

    std::cout << '\n';
    arthur.describe();
    birds.back()->describe();

    std::cout << '\n';
    arthur.feed();
    birds.back()->feed();

    // amy.feed();
    // bob.feed();
    // carl.feed();

    // polly.feed();
    // sammy.feed();
}
