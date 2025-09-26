//
// Created by tuuli on 04/09/2025.
/*
Write a program that defines a map<string, int>

Program asks user to enter a name or “stop” or “print”. If user enters “stop” the program stops. If
user enters “print” then the program prints the content of the map as key-value pairs. If input is
neither “stop” not “print” then program asks user to enter an integer. Then program uses the
entered name as the key (~index to map) to store the entered integer.

To get the keys from the map you need to use iterators or range-for to loop through the map. When
looping through the map the elements of the map are std::pairs that contain key and the value. If
using iterator, the iterator “points” to a pair where first is key and second is the value. For example, if
your iterator is called it then key of the current element is it->first and value is it->second.

For example:
Enter name or “stop” or “print”: Keijo
Enter integer: 77
Enter name or “stop” or “print”: Erkki
Enter integer: 23
Enter name or “stop” or “print”: What
Enter integer: 5
Enter name or “stop” or “print”: print
Erkki : 23
Keijo : 77
What : 5
Enter name or “stop” or “print”: Himmel
Enter integer: 99
Enter name or “stop” or “print”: print
Erkki : 23
Himmel : 99
Keijo : 77
What : 5
Enter name or “stop” or “print”: Himmel
Enter integer: 55
Enter name or “stop” or “print”: print
Erkki : 23
Himmel : 55
Keijo : 77
What : 5
Enter name or “stop” or “print”: stop
<program stops>
*/
/*
 Käyttöliittymä
 1. Ota inputtia
 2. Tallenna mappiin
 3. Print funktio
 4. Stop
 luo map
 while loopissa, kunnes stop
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

//INITIALIZE



//FUNCTIONS
std::string TakeStringInput() {
    std::string name;
    std::cout << "Enter a name or \"stop\" or \"print\": " << std::endl;
    //tähän väliin vois pistää virheen käsittelyn siit että syöte on asiallinen stringi
    //nyt esim välilyönnin laittaminen aiheuttaa endless loopin syötteen kyselyitä
    std::cin >> name;
    return name;
}

int TakeIntInput() {
    int num;
    std::cout << "Enter a number: " << std::endl;
    //tähän väliin vois laittaa virheen käsittelyn siitä että syöte on asiallista ja oikeesti int
    std::cin >> num;
    return num;
}

void PrintMap(const std::map<std::string, int> &map) {
    if (map.empty()) {
        std::cout << "No name-number pairs entered yet" << std::endl;
    }
    else {
        for (auto [fst, snd]: map) {
            std::cout << fst <<": " << snd << std::endl;
        }
    }
}

void PutToMap(std::map<std::string, int> &map, std::string key) {
    int num = TakeIntInput();
    //map[key]=num;
    std::pair<std::string, int> p = {key, num};
    map.insert(p);
}

//MAIN
int main() {
    bool keepGoing = true;
    //initialize a map
    std::map<std::string, int> nameMap;

    while (keepGoing) {
        std::string word = TakeStringInput();
        //std::string word2 = transform(word.begin(), word.end(), word.begin(), ::tolower);
        if (word == "stop") {
            keepGoing = false;
        }
        else if (word == "print") {
            PrintMap(nameMap);
        }
        else {
            PutToMap(nameMap, word);
        }
    }


    return 0;
}
