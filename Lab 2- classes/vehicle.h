#ifndef VEHICLE_H
#define VEHICLE_H


#include <string>
using namespace std;

class Vehicle {
    //variables
private:
    string make,model;
    int year;
    double price;
    int mileage;

public:

    Vehicle();


    Vehicle(string make, string model, int year, float price, int mileage);


    void Display();

    //return string
    string GetYearMakeModel();

    // return price
    float GetPrice();
};

#endif
