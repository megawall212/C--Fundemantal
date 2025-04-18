
#ifndef DEALERSHIP_H
#define DEALERSHIP_H

#include <string>
#include <vector>
#include "Showroom.h"

class Dealership {
private:
    std::string name;
    std::vector<Showroom> showrooms;
    unsigned int capacity;

public:
    // need default constructor from instruction pdf
    Dealership(std::string name = "Generic leadership", unsigned int _capacity = 0);

    void AddShowroom(Showroom showroom);
    void ShowInventory();
    float GetAveragePrice();
    void ShowAveragePrice();  // copy all the method from instruction file
};
#endif // end that pls!
