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
class Items {
private:
    std::string name;
    int weight;
    double price;
    int storage_amount;

public:
    Items() {
        name = "Item unknown";
        weight = 100;
        price = 10;
        storage_amount = 1;
    }
    Items(std::string n, int w, double p, int s){
        name = n;
        weight = w;
        price = p;
        storage_amount = s;
    }
    bool operator<(const Items &val) const {
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

    friend std::ostream &operator<<(std::ostream &out, const Items &i); //output overloaded operator
    friend std::istream &operator>>(std::istream &in, Items &i);      //input overload operator
};

//FUNCTIONS
std::ostream &operator<<(std::ostream &out, const Items &i) {
    //{ "Name":"Diced chicken", "Weight":350, "Price":5.30, "Count": 1 }
    out << "{\"Name\":" << i.name << ", \"Weight\":" << i.weight << ", \"Price\":" << i.price << ", \"Count\":" << i.storage_amount << "}";
    return out;
}

std::istream &operator>>(std::istream &in, Items &i) {
    //tämä funktio ottaa vain json muotoista vastaa, loput syötteeet otetaan mainissa. Jos ei ole json muotoista, palauttaa failbitin
    std::string name = "{\"Name\":\"",
    weight = "\", \"Weight\":",
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

                    if (ssolio1 >> weight_num && ssolio2 >> price_num && ssolio3 >> count_num) {

                        ok = true;
                    }
                }
            }
        }
    }
    if (!ok) //pistä failbit päälle
    //Saat rivin syötteeseen, ja siitä kaivetaan sitten oikoeat tiedot ja tarkistetaan että muoto oikein.
    return in;
}

//MAIN
int main() {
    //määrittele täälä vektori rakenne
    std::vector<Items> iv;

    //pistä vektoriin sample kamaa
    iv.emplace_back("kana",350,5.5, 10);
    iv.emplace_back("banaani",150,0.5, 20);
for (auto &item:iv) {
    std::cout << item;
    std::cout << std::endl;
}
    //printtaa ensimmäisen alkion iv vektorista
    std::cout << iv.at(0);
    //std::cout << "Kissa konsolissa";
// step 1: output operaattori
// step 2: vertailu (<-operaattori)
// step 3: input operaattori


    return 0;
}


/*
 *Esimerkki siitä miten overloadatulla << operaattorilla voi esim tulostaa fileen asioita.
 *Helpottamaan ymmärtämistä miten overloadattu operaattori toimii, mitä sillä voi tehä.
std::ofstream of("testi.txt");
of << iv[0];
*/