#include "Vehicle.h"
#include <iostream>
using namespace std;

// Default constructor
Vehicle::Vehicle(){
    make = "COP3503";
    model = "Rust Bucket";
    year = 1900;
    price = 0.0;
    mileage = 0;
}

// redefined/parameterized(idk) constructor
Vehicle::Vehicle(string make, string model, int year, float price, int mileage) {
    this->make = make;
    this->model = model;
    this->year = year;
    this->price = price;
    this->mileage = mileage;
}

// display vehicle
void Vehicle::Display() {
    cout << year << " " << make << " " << model << " $" << price << " " << mileage << endl;
}

//year of model
string Vehicle::GetYearMakeModel() {
    return to_string(year) + " " + make + " " + model;
}

// get the price
float Vehicle::GetPrice() {
    return price;
}
