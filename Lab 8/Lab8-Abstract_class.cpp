//
// Created by tuuli on 03/10/2025.
//

#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <filesystem>
#include "Lab8-Abstract_class.h"


//COUNTER CLASS
Counter::Counter(int initial, int limit): count(initial), upLimit(limit) {}

std::ostream& operator<<(std::ostream& out, const Counter& ctr){    //friend function for overloading output operator
    out << ctr.count;
    return out;
}


//LIMITED COUNTER CLASS
LimitedCounter::LimitedCounter(int initial, int limit) :Counter(initial, limit) {}

void LimitedCounter::inc() {
    if(count < upLimit){
        count++;
    }
}
void LimitedCounter::dec() {
    if(count > 0){
        count--;
    }
}


//OVERFLOW COUNTER CLASS
OverflowCounter::OverflowCounter(int initial, const int limit) :Counter(initial, limit) {}

void OverflowCounter::inc() {
    count++;
    if(count > upLimit){
        count = 0;
    }
}
void OverflowCounter::dec() {
    count--;
    if(count < 0){
        count = upLimit;
    }
}

//OTHER FUNCTIONS
void UseCounter(Counter& ctr, int num)
{
    if (num > 0) {
        for (int i = 0; i < num; ++i) {
            ctr.inc();
        }
    } else if (num < 0) {
        for (int i = num; i < 0; ++i) {
            ctr.dec();
        }
    }
}
