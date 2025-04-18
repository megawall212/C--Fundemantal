#ifndef SHOWROOM_H
#define SHOWROOM_H
#pragma once // it's optional


#include "Vehicle.h"
#include <vector>
#include <string>

class Showroom
{
private:
    std::string name;
    std::vector<Vehicle> vehicles;
    // variable from lab 2 instruction file
    unsigned int capacity;

public:
    // Default constructor
    Showroom(std::string name = "Unnamed Showroom", unsigned int capacity = 0);

    // Return the vector <Vehicle> objects
    std::vector<Vehicle> GetVehicleList();

    // Behaviors
    void AddVehicle(Vehicle v);
    void ShowInventory();
    float GetInventoryValue();
};

#endif // SHOWROOM_H
