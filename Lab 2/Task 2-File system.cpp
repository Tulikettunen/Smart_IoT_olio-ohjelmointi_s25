//
// Created by tuuli on 29/08/2025.
/*Std::filesystem abstracts path handling and directory creation. The library provides functionality to
resolve relative path to absolute path and operators for easy building of paths in a platform
independent way.
Std::filesystem::path has overloaded operators for creating a path by concatenating paths or strings.
The resulting path can be used to open files or for example, to create multiple directories.
Implement a program that asks user to enter directory names or enter a blank line to stop entry. The
read names are stored in a vector of strings. When user has stopped entering directory names the
program forms a relative path from the entered directory names. For example, if user entered “this”,
“is”, and “test” the path is “this/is/test” (assuming posix operating system, Windows uses backslash
as the separator ). To form a path use append operator defined for std::filesystem::path.
Then program creates the path using create_directories (see:
https://en.cppreference.com/w/cpp/filesystem/create_directory ). After creating the directory, the
program opens a text file “result.txt” for writing in the created directory and outputs the following
both to screen and the file:
• Absolute path to the file (there is a function to get that)
• Content of the string vector one element per line
• Relative path to the file
Note that since C++17 ofstream (and fstream in general) constructor can take filesystem::path as
parameter.
*/
//

//INCLUDE
#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>

//INITIALIZE
std::vector<std::string> input();


//FUNCTIONS
std::vector<std::string> input(){
    std::string line;
    getline(std::cin, line);

}


//Ohjelman oletus on että sinne ei pistetä nimiin välilyöntejä, kiitos!!

//MAIN
int main() {
    //Alustetaan tarvittavia asioita
    std::string line;
    std::vector<std::string> names;
    std::istringstream ssolio;
    bool stop = false;

    //While loop jolla otetaan käyttäjältä kansion nimiä ja siirretäänn ne string line muuttujaan,
    //jonka kautta ne siirretään names vektoriin talteen. Loop loppuu kun käyttäjä painaa tyhjän rivin enterillä.
    while (stop == false) {
        std::cout << "Enter a directory name and press enter, or press enter to empty line to stop: " << "\n";
        getline(std::cin, line);

        if (line.empty()) {
            stop = true;
        }
        else {
            names.push_back(line);
        }

    }

    //Testataan että kansioiden nimet menee string vectoriin oikein tulostamalla ne
    for (auto n: names) {
        std::cout << n << std::endl;
    }



    return 0;
}