//
// Created by tuuli on 06/09/2025.
/*
Implement a class for calculaIng running average of a number of values. The idea of running average
that average is calculated of last N values. For example, when running average of last 10 values is
calculated every Ime a new value is added if there are already 10 values the oldest value is removed.
Implement a class called RunningAverage:

• Constructor takes number of values as a parameter for example:
RunningAverage avg(5);
Creates an instance that remember five last values.

• A deque of integers is used to store the values

• Class has member funcIon void add_value(int value) which is used to add a new
value and to remove the oldest value if there are specified number of elements so that
number of values in the never exceeds the size given in the constructor.

• Class has member funcIon double get_average() that returns the average of the stored
values.

Write a program that creates running average object to calculate running average of last five
numbers. Program asks user to enter numbers and to enter zero to stop. If entered value is not zero
it is added to the running average and program prints the current running average. If value is zero the
program prints the current running average and then stops.
*/
//

//INCLUDE
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <filesystem>
#include <map>
#include <utility>
#include <deque>

//INITIALIZE
#define MAX_SIZE 5


//CLASSES
class RunningAverage {
public:
    int maxSize;
    //deque alustettu tässä atribuuttina luokalle
    std::deque<int> numbers;

    explicit RunningAverage(int N){
        maxSize = N;
    }

    void addValue(int value);
    double getAverage();
};


//FUNCTIONS
void RunningAverage::addValue(int value) {
    if (numbers.size() == maxSize) {
        //Luodaan fifomainen deque rakenne. eli ensimmäiseksi uusin, jos max määrä täynnä: vanhin eli viimeinen pois
        numbers.pop_back();
    }
    numbers.push_front(value);
}

double RunningAverage::getAverage() {
    double average = 0.0;
    for (auto i: numbers) {
        average = average + i;
    }
    average = average / maxSize;
    return average;
}

//ohjeessa ei ollut eritelty, mitä tehdä siihen asti, kun dequessa ei ole vielä täyttä listaa arvoja, kun ohjelma vasta aloitetaan.
//Toteutettu niin, että ohjelma kysyy numeroita siihen asti, että MAX_SIZE määrä on saatu, ja alkaa vasta sen jälkeen printtaamaan keskiarvoa
//Tuntu loogisemmalta niin.

//MAIN
int main() {
    bool keepGoing = true;
    RunningAverage avg(MAX_SIZE);

    while (keepGoing == true) {
        int value;
        std::cout << "Give a number, or enter a zero. Then I will calculate the running average of " << MAX_SIZE << " for you! :"<< std::endl;
        std::cin >> value;  //virheen käsittely puuttuu edelleen..

        if (value == 0) {
            std::cout << "The last running average is: " << avg.getAverage()<< std::endl;
            std::cout << "You have stopped the program.";
            keepGoing = false;
        }
        else {
            avg.addValue(value);
            if (avg.numbers.size() == MAX_SIZE) {
                std::cout << "The running average is: " << avg.getAverage() << std::endl;
            }
        }
    }

    return 0;
}


