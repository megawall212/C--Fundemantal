//
// Created by lzy46 on 3/17/2025.
//
// Dealership.cpp
#include "Dealership.h"
#include "Showroom.h"
#include <iostream>
#include <vector>
#include <iomanip>  // For setting output precision

Dealership::Dealership(string name, unsigned int _capacity)
{
    name = name;
    capacity = _capacity;
}

void Dealership::AddShowroom(Showroom showroom) {
    if (showrooms.size() == capacity) {  // set that equals to capacity
        // don't set it to 3
        std::cout << "Dealership is full, can't add another showroom!" << std::endl;
        return;
    }
    showrooms.push_back(showroom);
}

void Dealership::ShowInventory() {
    if (showrooms.empty()) {
        std::cout << "Generic Dealership is empty!" << std::endl;
        //return;


    }else{

        for (auto& showroom : showrooms) {
            showroom.ShowInventory();  // call that function from showroom
            std::cout << std::endl;
        }

    }
    cout << "Average car price: $" << GetAveragePrice();
}

float Dealership::GetAveragePrice() {
    float totalPrice = 0;
    int vehicleCount = 0;

    for (auto& showroom : showrooms) {
        std::vector<Vehicle> vehicles = showroom.GetVehicleList();  // Get vehicle list from Showroom
        for (auto& vehicle : vehicles) {
            totalPrice += vehicle.GetPrice();
            vehicleCount++;
        }
    }

    // check the average price
    if (vehicleCount == 0) {
        return 0;  // If there are no vehicles, return 0
    }
    return totalPrice / vehicleCount;
}
/*
return vehicleCount == 0 ? 0 : totalPrice / vehicleCount; (gpt version)
it saves 2 decimal
*/


// don't need that function, everything should be fine with getprice

/*
void Dealership::ShowAveragePrice() {
    float averagePrice = GetAveragePrice();
    std::cout << "Average price of the cars in the dealership: $"
              << std::fixed << std::setprecision(2) << averagePrice << "-e";  // No space after "-e"
    std::cout << std::endl; // Move the newline here
}
*/



