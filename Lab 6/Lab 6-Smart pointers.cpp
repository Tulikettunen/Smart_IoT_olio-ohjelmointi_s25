//
// Created by tuuli on 23/09/2025.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <string>
#include <bits/stdc++.h>
#include <filesystem>
#include <memory>
#include "C:/Users/tuuli/CLionProjects/Own_headers/My_header.h"

//INITIALIZE

//CLASSES

class House {
private:
    std::string address;
    double area;
    double price;
public:
    House(std::string address, double area, double price) : address(std::move(address)), area(area), price(price){}
    //output operator:  printing the housing information with minimal formatting. No newlines may be printed by the operator
    void operator << (const House &i) const;
    // < (less than) operator that compares two houses by price/m2
    bool operator < (const House& H) const;
    void setAddress();
    std::string getAddress();
    void setArea();
    void setPrice();
};


class Apartment {
private:
    //shared_pointer to House class,
    //jokasella asunnolla pitää olla smart pointer Houseensa
    //pointerilla pitää saada asunnon osoite
    std::shared_ptr<House> house; //konstruktori ottaa parametrikseen sharedpointerin, joka on Talo
    //as_nro, size, rent
    int as_nro;
    double size;
    double rent;
public:
    Apartment(std::shared_ptr<House> house, int as_nro, double size, double rent) : house(std::move(house)), as_nro(as_nro), size(size), rent(rent) {}
    // a member function that prints the apartment information
    // Address and apartment nr, Size of the apartment, The monthly rent
    void print() {
        std::cout << house->getAddress() << " " << as_nro << ", "<< size << "m^2, " << rent << "/kk." <<std::endl;
    }
    // < (less than) operator that compares apartments by monthly rent
    bool operator < (const Apartment& As) const;
};


//CLASS FUNCTIONS

//House:
void House::operator << (const House &i) const {
    std::cout << "Address:" << i.address << ", " << i.area << "m^2, " << i.price << "€.";
}

bool House::operator < (const House& H) const {
    //compare houses price/m^2
    double self_pricem2 = price / (area * 1.0);
    double H_pricem2 = H.price / (area * 1.0);
    if (self_pricem2 < H_pricem2) {
        return true;
    }
    return false;
}

void House::setAddress() {
    std::getline(std::cin, address);
}

std::string House::getAddress() {
    return address;
}

void House::setArea() {
    area = numberInput(area);
}

void House::setPrice() {
    price = numberInput(price);
}

//Apartment:
bool Apartment::operator < (const Apartment& As) const {
    //compare apartments by monthly rent
    if (rent < As.rent) {
        return true;
    }
    return false;
}



//MAIN
int main() {
    //luo vektori
    std::vector<Apartment> apartments;
    //3 as ekaan taloon, 4 as tokaan taloon, lisää ne vektoriin
    auto talo1 = std::make_shared<House>("Kissakatu 4", 450, 3400000);
    auto talo2 = std::make_shared<House>("Pääskypolku 16", 640, 6500000);

    apartments.emplace_back(talo1, 56, 31.5, 560.4);
    apartments.emplace_back(talo1, 12, 47, 890.8);
    apartments.emplace_back(talo1, 4, 87, 1356.75);

    apartments.emplace_back(talo2, 25, 24.5, 576.3);
    apartments.emplace_back(talo2, 90, 67, 1490.9);
    apartments.emplace_back(talo2, 74, 45.5, 945.85);
    apartments.emplace_back(talo2, 1, 14.5, 458.9);

    //lajittele ja printtaa vektori
    std::sort(apartments.begin(), apartments.end());
    for (auto &i: apartments) {
        i.print();
    }
}


/*Esim koodi syntaxista
    auto talo = std::make_shared<House>("katu",600, 2600000);
    shared_pointer, joka luo instanssin talosta.
    Talo pointerista annetaan kopio parametrina apartmentin construktorille, jotta jokaine asunto on talossa
    shared_ptr<Rectangle> P1(new Rectangle(10, 5));
    cout << P1 -> area() << endl;
    */