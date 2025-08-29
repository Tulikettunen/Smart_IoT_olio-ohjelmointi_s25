//
// Created by tuuli on 22/08/2025.
/*Simple C++ program
Write a program that defines an empty vector of integers. Then program asks user how many
numbers he/she wants to enter. Then program asks user to enter the numbers one at a time and
adds them to the vector. When all number have been entered the program prints the numbers in the
vector.
For example:
How many numbers do you want to enter? 4
Enter nr[1]: 23
Enter nr[2]: 12
Enter nr[3]: 4
Enter nr[4]: 5
You entered: 23, 12, 4, 5
*/
//
// INCLUDES:

#include <vector>
#include <iostream>

// INITIALISE FUNCTIONS:
std::vector<int> CreateVector();
void AddToVector(std::vector<int>* vect);
int InputTaker();

// FUNCTIONS:
std::vector<int> CreateVector() {
    std:: vector<int> numbers;
    //Luodaan usi vektori nimeltä numbers
    return numbers;
    //Joo, funktio tälle tässä kohtaa vielä turha, mut tulee opeteltua vektorien käyttämistä funktioissa
}

void AddToVector(std::vector<int>* vect, int x) {       // int tyyppisen vektorin pointteri parametriksi, ja ihan kopio x muuttujasta riittää
    vect->push_back(x); //vect vectorimuuttujaan (johon on otettu pointteri funktion parametreissa)
    //käytetään metodia push_back, joka lisää muuttujan x vektorin perälle
}

int InputTaker() {
    int x;
    std:: cin >> x;     // Tässä ei ole vielä virheen käsittelyä. Otetaan x muuttujalle input standard inputilla (cin)
    return x;
}

//MAIN:
int main(){
    //Luo vektori
    std:: vector<int> numbers = CreateVector();

    //Kysy kuinka monta numeroa haluaa syöttää
    std:: cout << "You can give me numbers, and I'll print them to you" << "\n";
    std:: cout << "How many numbers do you want to give?" << "\n";
    int amount = InputTaker();

    //kysytään loopilla syötettävät numerot
    for (int i = 1; i <= amount; ++i) {
        std::cout << "Give number " << i << "\n";
        int num = InputTaker();
        AddToVector(&numbers, num);
    }

    //Printataan vektorin sisältö
    std:: cout << "Your list is: ";
    for (int i = 0; i < numbers.size(); ++i) {
        if (i+1 < numbers.size()){
            std:: cout << numbers[i] << ", ";
        }
        else {
            std:: cout << numbers[i];
        }
    }
    std::cout << "\n";


return 0;
}