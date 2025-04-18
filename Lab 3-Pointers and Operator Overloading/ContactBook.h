//
// Created by lzy46 on 3/17/2025.
//

/*

#include <string>
#include <vector>
#include <iostream>
//be careful about pointers/ operation overloading
//no dynamic memory or const
//also case sensitive

class Contact {
  // Write the class
};

class ContactBook {
  // Write the class
};

*/

#ifndef CONTACTBOOK_H
#define CONTACTBOOK_H

#include <string>
#include <vector>
#include <algorithm> // For std::sort
#include <iostream>  // For std::cout

//need those two

// Maximum number of contacts from the instruction
#define MAX_SIZE 100

// Contact class declaration
class Contact {
private:
    std::string name;
    std::string number;

public:
    Contact(std::string name, std::string number); // Constructor
    std::string getName(); // Getter for name
    std::string getNumber(); // Getter for number
    void display(); // Display method
};

// ContactBook class
class ContactBook {
private:
    Contact* contacts[MAX_SIZE]; // make array of Contact pointers
    unsigned int curr_size; // Current size of the ContactBook

public:
    ContactBook(); // Default constructor

// One of the Tas told me i can comment this line out
/*
    ContactBook(ContactBook& other); // Copy constructor
    ContactBook& operator=(const ContactBook& other); // Assignment operator
    ~ContactBook();
  */

    Contact* Find(std::string query); // Find contact by name/ number
    void Add(Contact& contact); // Add a contact to the ContactBook
    void AddContacts(std::vector<Contact*> newContacts); // Add multiple contacts
    void Remove(Contact& contact); // Remove a contact from the ContactBook
    void Display(); // Display all contacts in the ContactBook
    void Alphabetize(); // Alphabetize the contacts

    // Operator overloads
    ContactBook& operator+=(Contact& contact); // Add a single contact
    ContactBook& operator+=(ContactBook& other); // Add all contacts from another ContactBook
    ContactBook operator+(ContactBook& other); // Add two ContactBooks
    ContactBook& operator-=(Contact& contact); // Remove a single contact
    ContactBook& operator-=(ContactBook& other); // Remove all contacts from another ContactBook
    ContactBook operator-(ContactBook& other); // Subtract two ContactBooks

    bool operator==(ContactBook& other); // Compare two ContactBooks for equality
    bool operator!=(ContactBook& other); // Compare two ContactBooks for inequality
};

#endif

