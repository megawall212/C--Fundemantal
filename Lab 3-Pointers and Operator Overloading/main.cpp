#include <iostream>
#include "ContactBook.h"

/* DO NOT WRITE YOUR CLASS IN THIS FILE
// This file is only to debug your own class/code using the
// Code Visualizer buttons in the Guide
// The test cases below will completely ignore this file

int main() {

  ContactBook book;
  // Your testing if you would like

  return 0;
}
*/

#include "ContactBook.h"
#include <iostream>

//just for testing

int main() {
    Contact test1("Roland", "456-789-0123");
    Contact test2("Andres", "987-654-3210");
    Contact test3("George", "234-567-8901");
    Contact test4("Albert", "555-555-5555");
    Contact test5("Alberta", "111-222-3333");

    ContactBook ContactBook1;
    ContactBook1.Add(test1);
    ContactBook1.Add(test2);
    ContactBook1.Add(test3);
    ContactBook1.Add(test4);
    ContactBook1.Add(test5);

    ContactBook1.Display();

    if (ContactBook1.Find("987-654-3210") == &test2) {
        std::cout << "Found the contact!" << std::endl;
    }

    if (ContactBook1.Find("Doesnt-Exist") == nullptr) {
        std::cout << "Contact not found!" << std::endl;
    }

    return 0;
}
