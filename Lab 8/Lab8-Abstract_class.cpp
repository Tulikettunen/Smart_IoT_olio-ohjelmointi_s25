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
