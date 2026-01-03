//
// Created by tuuli on 26/09/2025.
//

//INCLUDE
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <filesystem>

//#include "My_header.h"
#include "C:/Users/tuuli/CLionProjects/Own_headers/My_header.h"

//CLASSES
class Person {
    //holds a person’s name and prints it when needed.
public:
    explicit Person(const char *name = "nobody");
    virtual ~Person() = default;
    virtual void identity() const;  //prints the name of the person.
    virtual void interrogate(){}     //does nothing (empty body) in class Person.
private:
    std::string name;
};


class Spy: public Person {
public:
    Spy(const std::string& name, std::string alias, int resistance);
    void set_identity(const char *alias);   //member function that can be used to set an alias for the spy.

    //When resistance is greater than zero, prints alias of the spy instead of the real name.
    //When resistance is zero, prints both the real name and the alias of the spy
    void interrogate() override;
    void identity() const override;
    //The real name of the spy is inherited from the Person class.
    //Spy adds a private member to hold the alias that spy uses until resistance runs out.

private:
    std::string alias;
    int resistance;
};

//CLASS FUNCTIONS
Person::Person(const char *name) : name(name){}

void Person::identity() const{
	std::cout << "My name is " << name << std::endl;
}


Spy::Spy(const std::string& name, std::string alias, const int resistance) : Person(name.c_str()), alias(std::move(alias)), resistance(resistance) {
}

void Spy::identity() const{
	if(resistance > 0){
	std::cout << "My name is " << alias << std::endl;
	}
	else{
	Person::identity();
	std::cout << "My alias is " << alias << std::endl;
	}
}

void Spy::set_identity(const char *alias){
    this->alias = alias;
}

void Spy::interrogate(){
if (resistance > 0){
	resistance = resistance -1;
	}
}

//class Person:
//virtual void Person::identity() const {}  //tätä ei voi määrittää jos se on virtual?
//pitää alustaa, ja overridaa sit perityssä luokassa?

//class Spy:



//MAIN (GIVEN)
int main(int argc, char** argv) {
    Person agent("James Bond");
    Spy spy("Emilio Largo", "William Johnson", 3);
    Spy spy2("Ernst Blofield", "John Keats", 5);
    std::cout << std::endl << "Nice to meet you. ";
    agent.identity();
    for (int i = 0; i < 6; ++i) {
        std::cout << "Who are you?" << std::endl;
        spy.interrogate();
        spy.identity();
    }
    spy.set_identity("Bill Munny");
    spy.identity();
    std::cout << std::endl << "Nice to meet you. ";
    agent.identity();
    for (int i = 0; i < 6; ++i) {
        std::cout << "Who are you?" << std::endl;
        spy2.interrogate();
        spy2.identity();
    }
    return 0;
}