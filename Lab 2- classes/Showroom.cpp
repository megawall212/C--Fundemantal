//
// Created by lzy46 on 3/17/2025.
//
#include "Showroom.h"
#include <iostream>

//debugging: don't make variable const
// make then as modifiable reference
//allowing calls to non-const methods.

using namespace std;

// Constructor
Showroom::Showroom(string name, unsigned int capacity) : name(name), capacity(capacity) {}

// Get method
vector<Vehicle> Showroom::GetVehicleList() {
    return vehicles;
}

// AddVehicle method
void Showroom::AddVehicle(Vehicle v) {
    if (vehicles.size() >= capacity) {
        // GetYearMakeModel()function from the Vehicle class
        cout << "Showroom is full! Cannot add " << v.GetYearMakeModel() << endl;
    } else {
        vehicles.push_back(v);
    }
}

// ShowInventory method
void Showroom::ShowInventory() {
    if (vehicles.empty()) {
        cout << name << " is empty!" << endl;
        return;
    }

    cout << "Vehicles in " << name << endl;  // Print the showroom name before listing vehicles

    for (auto& vehicle : vehicles) {
        vehicle.Display();
    }
}


// Sumup the prices of all vehicles
float Showroom::GetInventoryValue() {
    float total = 0;
    for (auto& vehicle : vehicles) {
        total += vehicle.GetPrice();
    }
    return total;
}
