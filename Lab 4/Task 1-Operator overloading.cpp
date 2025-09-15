//
// Created by tuuli on 08/09/2025.
// step 1: output operaattori
// step 2: vertailu (<-operaattori)
// step 3: input operaattori
//step 4: normi input else lauseeseen
//step 6: print list (indekseillä) and networth of the stock
//step 7: kysy mitä halutaan muuttaa (based on index) ja muutetaan
//step 8: sort and print again
//step 5: sort vektori (< operator tehty valmiiks, käytetään sitä)
//

//INCLUDE
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <filesystem>


//CLASSES
class Item {
private:
    std::string name;
    int weight;
    double price;
    int storage_amount;

public:
    Item() {
        name = "Item unknown";
        weight = 100;
        price = 10;
        storage_amount = 1;
    }
    Item(std::string n, int w, double p, int s){
        name = n;
        weight = w;
        price = p;
        storage_amount = s;
    }
    bool operator<(const Item &val) const {
        //compare based on weight per price number
        double const self_kilos = weight / 1000.0;
        double const val_kilos = val.weight / 1000.0;
        if ((price / self_kilos) < (val.price / val_kilos)) {
            return true;
        }
        return false;
    }

    int getCount() {
        return storage_amount;
    }
    void setCount(int a) {      //Tätä ei käytetä missään???
        storage_amount = a;
    }
    double getPrice() {
        return price;
    }
    void setPrice(double p) {
        price = p;
    }

    friend std::ostream &operator<<(std::ostream &out, const Item &i); //output overloaded operator
    friend std::istream &operator>>(std::istream &in, Item &i);      //input overload operator
};


//FUNCTIONS:

//Output stream overload operator
std::ostream &operator<<(std::ostream &out, const Item &i) {
    //{ "Name":"Diced chicken", "Weight":350, "Price":5.30, "Count": 1 }  Esimerkki formaatti
    out << "{\"Name\":" << i.name << ", \"Weight\":" << i.weight << ", \"Price\":" << i.price << ", \"Count\":" << i.storage_amount << "}";
    return out;
}

//Input stream overload operator
std::istream &operator>>(std::istream &in, Item &i) {
    //tämä funktio ottaa vain json muotoista vastaa, loput syötteeet otetaan mainissa. Jos ei ole json muotoista, palauttaa failbitin
    std::string name = R"({ "Name":")",
    weight = R"(", "Weight":)",
    price = ", \"Price\":",
    count = ", \"Count\":";
    bool ok = false;
    std::string line;
    std::getline(in, line, '}');    //ota getlinella } asti, käytä sitä erottimena.
    if ( line.find(name) != std::string::npos) {
        auto name_i = line.find(name);
        if (line.find(weight, name_i) != std::string::npos) {
            auto weight_i = line.find(weight);
            if (line.find(price, weight_i) != std::string::npos) {
                auto price_i = line.find(price, weight_i);
                if (line.find(count, price_i) != std::string::npos) {
                    auto count_i = line.find(count, price_i);
                        //Tässä kohtaa on tarkistettu että Json formaatti on ok. sitä onko paino, hinta ja määrä pelkkiä lukuja ei vielä.
                        //tarkistus string stream oliolla ja if lauseella. Jaetaan line stream olioille indeksien mukaan, jotta saadaan se mitä halutaan ulos
                    std::string name_str = line.substr(name_i + name.size(), weight_i - (name_i + name.size()));
                    std::istringstream ssolio1(line.substr(weight_i + weight.size(), price_i - (weight_i + weight.size())));
                    std::istringstream ssolio2(line.substr(price_i + price.size(), count_i - (price_i + price.size())));
                    std::istringstream ssolio3(line.substr(count_i + count.size(), line.size() - (count_i + count.size())));
                    int weight_num;
                    double price_num;
                    int count_num;
                    //Tän pitäisi antaa automaattisesti failbit jos tulosta ei saada??
                    //Jos kaikki onnistuu, niin if lauseen sisällä referenssinä otettuun olioon asetetaan constructorilla saadut parametrit
                    if (ssolio1 >> weight_num && ssolio2 >> price_num && ssolio3 >> count_num) {
                        i = Item(name_str, weight_num, price_num, count_num);  //Laitetaan kamaa referenssattuun olioon
                        ok = true;
                    }
                }
            }
        }
    }
    if (!ok) {  //pistä failbit päälle jos ei ok, ja json ei mennyt läpi
        in.setstate(std::ios::failbit);
    }
    return in;
}

//print vector ja networth functio
void printVector(std::vector<Item> &v) {
    int count = 0;      //index
    double networth = 0;
    for (auto &i:v) {
        std::cout << "[" << count << "]";
        std::cout << i;
        std::cout << std::endl;
        //ottaa kyseisen indeksin hinnan, ja kpl määrän, kertoo keskenään, ja lisää aikaisempaan kertymään
        networth = networth + i.getPrice()*i.getCount();
        ++count;
    }
    std::cout << "Networth of your stock is: " << networth << std::endl;
}

//MAIN
int main() {
    //määrittele täälä vektori rakenne
    std::vector<Item> iv;
    bool keepGoing = true;

    //main koodia. Syöte funktio:
    while (keepGoing == true) {
        Item newItem;
        std::cout << R"(Enter item information, starting with the name or "stop" to end entering items or "json" to enter item information in JSON format)" << std::endl;
        std::string line;
        std::cin >> std::ws;    //tyhjentää cin:in bufferista white spacet, joutuu muuten ikuiseen looppiin rivien 147 ja 151 välillä..
        std::getline(std::cin, line);
        if (line == "stop") {   //jos kirjoitettu stop, mennään tänne
            keepGoing = false;
        }
        else if (line == "json") {  //jos valittu json, mennään tänne
            std::cout << "Enter the JSON" << std::endl;
            std::cin >> newItem;
            if (std::cin.fail()) {      //jos json data ei ollut ok, mennään tänne ja ilmoitetaan käyttäjälle, myös estää ojelman kaatumisen
                std::cout << "Something went wrong when parsing json." << std::endl;
                std::cin.clear();   //tyhjentää päälle menneen failbitin pois uutta kierrosta varten.
            }
            else {
                iv.emplace_back(newItem);   //jos kaikki putkeen jsonilla, lisätään uusi olio vektoriin
            }
        }
        else {      //muuten mennään tänne, ja käytetään annettua syötettä nmenä, mitä ikinä sisältääkään
            //Tähän laitetaan suoraan nimellä alotettava syöte uuden olion parametrien antamiseksi
            int weight_num;
            double price_num;
            int count_num;
            //Tässä kohtaa ei voi laittaa virhesyötettä!
            std::cout << "Enter weight: " << std::endl;
            std::cin >> weight_num;
            std::cout << "Enter price: " << std::endl;
            std::cin >> price_num;
            std::cout << "Enter how much in stock: " << std::endl;
            std::cin >> count_num;
            iv.emplace_back(line, weight_num, price_num, count_num);
        }
    }

    //stopin jälkeen päädytään tänne, ja printataan vektori indekseineen, ja lopuksi "varaston" nettoarvo
    std::sort(iv.begin(), iv.end());
    printVector(iv);

    //seuraavaksi kysytään käyttäjältä minkä tuotteen hinnan haluaa muuttaa, ja tehdään hintaan muutos.
    auto index = 0;
    double new_price;
    std::cout << "Enter an index of the item you wish to change price for: " << std::endl;
    std::cin >> index;  //tässäkään ei ole virheen käsittelyä, pitää syöttää oikeasti numeroita!
    std::cout << "Enter the new price: " << std::endl;
    std::cin >> new_price;
    iv[index].setPrice(new_price);
    sort(iv.begin(), iv.end());
    printVector(iv);

    return 0;
}

//testidataa:
//   { "Name":"Chicken vindalo", "Weight":1000, "Price":17.90, "Count": 2 }
//   { "Name":"Ketsuppi", "Weight":1000, "Price":3.20, "Count": 3 }
//   { "Name":"Pizza buffa", "Weight":1000, "Price":12.80, "Count": 7 }