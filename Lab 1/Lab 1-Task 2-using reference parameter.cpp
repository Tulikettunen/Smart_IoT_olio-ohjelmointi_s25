//
// Created by tuuli on 28/08/2025.
/* Using reference parameter
Write a function that takes a reference to string and a character (by value) as parameters. The
function replaces all occurrences of the character with underscores.

Write a program that asks user to enter a string. Then program asks user to enter character to replace
or “stop” to stop the program. Note that program must read a string after the second question to be
able to test for “stop”. If answer is not “stop” then program passes the first character of second
question’s answer as the character to replace. Then program prints the string and continues. If
answer is “stop” the program ends.

For example:
Enter a string: This is a test
Enter character to replace or “stop”: i
Result: Th_s _s a test
Enter a string: I love C++
Enter character to replace or “stop”: stop*/
//

#include <vector>
#include <iostream>
#include <string>
#include <algorithm>


//INITIALISE FUNCTIONS
void ReplaceChar(std::string &stringi, char x);
std::string InputTaker();



//FUNCTIONS
void ReplaceChar(std::string &stringi, char x) {

    /*str1.replace(pos, n, m, c)
    pos: Index to the position in str1 where we have to start replacing the characters.
    n: Number of characters which we have to replace.
    m: Number of times we have to repeat the single character.
    c: Character by which we have to replace.*/

    for (int i = 0; i < stringi.size(); ++i) {
        if (stringi[i] == x) {
            stringi.replace(i, 1, 1, '_');
        }
    }
}   //n: vois ottaa vaihdettavan merkin (x) inputin pituuden, ja pistää sen myös m kenttään, niin pystyis vaihtaan useempia merkkejä

std::string InputTaker() {
    std::string text;
    std::getline(std::cin, text);
    return text;
}

//MAIN
int main() {
    //kysy ensin stringiä
    //while loop
        //kysy millä haluu korvata
        //tsekkaa stoppi
        //korvaa, kysy uudestaan

    std:: cout << "Enter a string:" << "\n";
    std::string string1 = InputTaker();
    bool stop = true;

    while(stop){
        std:: cout << "Enter character to replace or \"stop\":" << "\n";
        std::string string2 = InputTaker();
        if( string2 == "Stop" || string2 == "STOP" || string2 == "stop"){
            stop = false;
            break;
        }
    char letter = string2[0];
    ReplaceChar(string1, letter);
    std:: cout << "Result: " << string1 << "\n";
    }
    return 0;
}

