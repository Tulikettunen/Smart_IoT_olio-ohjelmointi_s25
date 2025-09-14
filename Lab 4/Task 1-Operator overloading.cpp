//
// Created by tuuli on 08/09/2025.
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
    void setCount(int a) {
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
    //{ "Name":"Diced chicken", "Weight":350, "Price":5.30, "Count": 1 }
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
                        //Tässä kohtaa on tarkistettu että Json formaatti on. sitä onko paino hinta ja määrä pelkkiä lukuja ei vielä.
                    //tarkistuksen voi tehdä mm stoi?? funktiolla, string to int funktiolla tms. ja string stream oliolla
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
    if (!ok) {  //pistä failbit päälle
        in.setstate(std::ios::failbit);
    }
    //Saat rivin syötteeseen, ja siitä kaivetaan sitten oikoeat tiedot ja tarkistetaan että muoto oikein.
    return in;
}

void printVector(std::vector<Item> &v) {
    int count = 0;      //index
    double networth = 0;
    for (auto &i:v) {
        std::cout << "[" << count << "]";
        std::cout << i;
        std::cout << std::endl;
        networth = networth + i.getPrice();
        ++count;
    }
    std::cout << "Networth of your stock is: " << networth << std::endl;
}

//MAIN
int main() {
    //määrittele täälä vektori rakenne
    std::vector<Item> iv;
    bool keepGoing = true;

    //pistä vektoriin sample kamaa
    iv.emplace_back("kana",350,5.5, 10);
    iv.emplace_back("banaani",150,0.5, 20);

    //main koodia. Syöte funktio:
    while (keepGoing == true) {
        Item newItem;
        std::cout << R"(Enter item information, starting with the name or "stop" to end entering items or "json" to enter item information in JSON format)" << std::endl;
        std::string line;
        //std::cout << "Is string good" << std::cin.good() << std::endl;      //Tarkistus output
        std::cin >> std::ws;
        std::getline(std::cin, line);
        //std::cout << line << std::endl;            //Tarkistus output
        if (line == "stop") {
            keepGoing = false;
        }
        else if (line == "json") {
            //testidataa:
            //   { "Name":"Chicken vindalo", "Weight":460, "Price":7.90, "Count": 2 }
            //   { "Name":"Ketsuppi", "Weight":200, "Price":3.20, "Count": 3 }
            //   { "Name":"Chicken buffa", "Weight":760, "Price":11.80, "Count": 7 }
            std::cout << "Enter the JSON" << std::endl;
            std::cin >> newItem;
            if (std::cin.fail()) {
                std::cout << "Something went wrong." << std::endl;
                std::cin.clear();
            }
            else {
                iv.emplace_back(newItem);
                std::cout << "Else if lause cin suoritettu" << std::endl;   //Tarkistus output
            }
        }
        else {
            //Tähän laitetaan suoraan nimellä alotettava syöte uuden olion parametrien antamiseksi
            //std::cout << "Vika else lause" << std::endl;    //Tarkistus output
            int weight_num;
            double price_num;
            int count_num;
            //Tässä kohtaa ei voi laittaa virhesyötettä
            std::cout << "Enter weight: " << std::endl;
            std::cin >> weight_num;
            std::cout << "Enter price: " << std::endl;
            std::cin >> price_num;
            std::cout << "Enter how much in stock: " << std::endl;
            std::cin >> count_num;
            iv.emplace_back(line, weight_num, price_num, count_num);
        }


    }

    printVector(iv);



    //printtaa ensimmäisen alkion iv vektorista
    //std::cout << iv.at(0);
    //std::cout << "Kissa konsolissa";
// step 1: output operaattori
// step 2: vertailu (<-operaattori)
// step 3: input operaattori
//step 4: normi input else lauseeseen
//step 6: print list (indekseillä) and networth of the stock

    //step 5: sort vektori (< operator tehty valmiiks, käytetään sitä)
//step 7: kysy mitä halutaan muuttaa (based on index) ja muutetaan
//step 8: sort and print again

    return 0;
}


/*
 *Esimerkki siitä miten overloadatulla << operaattorilla voi esim tulostaa fileen asioita.
 *Helpottamaan ymmärtämistä miten overloadattu operaattori toimii, mitä sillä voi tehä.
std::ofstream of("testi.txt");
of << iv[0];
*/