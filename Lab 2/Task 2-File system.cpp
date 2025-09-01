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
#include <filesystem>

//INITIALIZE
std::filesystem::path CreateDirectory(std::vector<std::string> dirNames);
std::filesystem::path CreateFilePath(std::filesystem::path dirPath, std::string& fileName);
void WriteToFile(std::filesystem::path filePath, std::vector<std::string> dirNames, std::string fileName);


//FUNCTIONS
std::filesystem::path CreateDirectory(std::vector<std::string> dirNames) {  //Luodaan kansiot ja kansiopolut, palauttaa kansiopolun.
    std::filesystem::path dirPath;

    for (auto n:dirNames) {     //Otetaan vektorista nimet, ja modostetaan niistä for-range loopilla kansiopolku
        dirPath = dirPath / n;
    }

    if (!exists(dirPath)) {
        create_directories(dirPath);        //luodaan kansiot
        std::cout << "Directory created: " << dirPath.string() << std::endl;    //Printataan käyttäjälle viesti onnistumisesta
    }

    return dirPath;
}

std::filesystem::path CreateFilePath(std::filesystem::path dirPath, std::string& fileName) {    //luodaan filelle nimi ja tiedostopolku
    fileName = fileName + ".txt";   //Lisätään nimen päätteeksi .txt
    std::filesystem::path filepath = dirPath / fileName;        //filepath variableen alustetaan/luodaan kansiopolulla ja txt tiedoston nimellä tiedostopolku

    return filepath;
}

void WriteToFile(std::filesystem::path filePath, std::vector<std::string> dirNames, std::string fileName){
    std::ofstream file(filePath);

    //Tarkistetaan onko file auki
    if (file.is_open()) {
        std::cout << "File created: " << filePath.string() << std::endl;
        std::cout << "File's contents: " << std::endl;

        //Printataan halutut tiedot fileen ja näytölle:
        file << "Absolute path to a file" << fileName << ": " << absolute(filePath).string() << std::endl;    //printataan fileen absoluuttinen polku käyttäen absolute() funktiota
        std::cout << "Absolute path to a file " << fileName << ": " << absolute(filePath).string() << std::endl;   //printataan näytölle absoluuttinen polku
        for (auto n: dirNames) {    //listataan allekkain kansioiden nimet omille riveilleen, fileen ja näytölle
            file << n << std::endl;
            std::cout << n << std::endl;
        }
        file << "Relative filepath to the file is: " << filePath.string() << std::endl;   //printataan fileen suhteellinen polku
        std::cout << "Relative filepath to the file is: " << filePath.string() << std::endl;  //printataan näyttöön suhteellinen polku
        file.close();   //suljetaan tiedosto
    }
    else {
        // virheen käsittely
        std::cerr << "Failed to create file: " << filePath
             << std::endl;
    }

}


//Ohjelman oletus on että sinne ei pistetä nimiin välilyöntejä, kiitos!!

//MAIN
int main(){
    //Alustetaan tarvittavia asioita
    std::string line;
    std::vector<std::string> dirNames;
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
            dirNames.push_back(line);
        }

    }

    std::string fileName = "return"; // Alustettu rakennusvaiheessa niin, että tätä voisi kehittää niin että käyttäjä pystyisi syöttämään oman haluamansa tiedostonimen.
    std::filesystem::path newDirPath = CreateDirectory(dirNames);
    std::filesystem::path newFilePath = CreateFilePath(newDirPath,fileName);
    WriteToFile(newFilePath, dirNames, fileName);

    return 0;
}
