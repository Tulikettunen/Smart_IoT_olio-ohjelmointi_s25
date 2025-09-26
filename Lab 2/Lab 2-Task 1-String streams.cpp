//
// Created by tuuli on 29/08/2025.
/*
 TEHTÄVÄNANTO:
Write a program that asks user to enter a line that contains integers or “stop” to stop the program. If
user enters a string that starts with “stop” the program stops. Otherwise, the program creates a
string stream from the user input and reads integers from the stream. Program keeps reading and
summing integer until the stream ends or reading an integer fails because text or other non-
numerical character is encountered. When the reading stops the sum and count are printed and
program asks user to enter another string.

For example:

Enter a line with numbers or “stop”: 1 6 34 78 4 6
Total of 6 numbers is 129
Enter a line with numbers or “stop”: 4 99 zip 44 6
Total of 2 numbers is 103
Enter a line with numbers or “stop”: stop
 *///

//INCLUDE:
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>


/*
 Millainen stop ratkaisu rakennettu:
 Ohjelma ottaa vastaan stringin, ja ensin tarkistaa pyytääkö käyttäjä missään kohtaa pysäyttämään ohjelman.
 Jos käyttäjä on kirjoittanut "stop" mihinkään väliin, ohjelma pysäytetään välittömästi, ja siitä ilmoitetaan käyttäjälle.
 Muutoin lasketaan syötetyt numerot yhteen ja alkioiden lukumäärä siihen asti kunnes syötteeseen tulee muuta kuin lukuja,
 tai rivi lopetetaan painamalla enter. Isoja ja pieniä kirjaimia ei ole otettu huomioon, pysäytyssana on spesifisti "stop" pienellä.
 */

//MAIN
int main() {
    int num;
    bool stoppi = false;
    std::string stop = "stop";

    //0. while loop, jonka sisällä ehtorakenteilla pyörii ohjelma, joka kysyy stop käskyyn asti numeroita listaan
    while (stoppi == false) {

    //1. Alustetaan numbers vektori ja line loopin alussa, jotta tyhjät uutta kierrosta varten. Vois myös opetella tyhjentään myöhemmin.
        std::vector<int> numbers;
        std::string line;

    //2. Kysytään käyttäjältä rivi, ja laitetaan se getlinella cin outputtia käyttämällä line stringiin talteen
        std::cout << "Enter a line with numbers or \"stop\":" ;
        getline(std::cin, line);

    //3. tähän väliin checkki stopille, ennen kun aletaan katsoa numeroita
                //s.find(sub);
                //  s= alkuperäinen stringi josta etsitään
                //  sub= substringi jota etsitään s:stä
        int res = line.find(stop);
        if (res != std::string::npos) {
            std:: cout << "You stopped the program." << std::endl;
            stoppi = true;
        }
    //4. jos stoppia ei löydy, etsitään numerot ja lasketaan ne yhteen jne
        else {
        //4.1 Aletaan pilkkoa line stringissä olevaa infoa numeroihin.
                //istringstream olio, nimetty ssolio:ksi, johon alustettu line stringissä tallessa oleva kama
            std::istringstream ssolio(line);

                //ssolio:sta otetaan num int muuttujaan välilyöntien välissä olevat numerot.
                //while loop pyörii niin kauan kuin numeroita onnistutaan saamaan, eli kunnes ssolio on tyhjä, tai törmätään ei-lukuun
                //Eli ehto täyttää overloadiin liittyvällä funktion metsästyksellä tuloksen true, kun onnistuu, false, kun ei.
                //siirretään num muuttujassa tallessa sillä kierroksella oleva luku push_back() metodilla numbers vektoriin.
            while (ssolio >> num) {
                numbers.push_back(num);
            }

        //4.2 Laskuri vectorin numbers numeroista, ja kuinka monta alkiota, + printtaa tuloksen
            auto howmany = numbers.size();
            int result = 0;
            for (auto n:numbers) {
                result = result + n;
            }
            std::cout << "Result of " << howmany << " numbers is " << result << std::endl;

            //for (auto n: numbers) std::cout << n << std::endl;    //testikäyttöön, printtaa tarvittaessa numerot terminaaliin
        }
    }



    return 0;
}