//
// Created by lzy46 on 3/17/2025.
//

#include "ContactBook.h"
#include <algorithm>
#include <iostream>

// Contact class implementation
#include "ContactBook.h"
#include <iostream>

// Contact class implementation
Contact::Contact(std::string name, std::string number) : name(name), number(number) {}

std::string Contact::getName() {
    return name;
}

std::string Contact::getNumber() {
    return number;
}

void Contact::display() {
    std::cout << name << ", " << number << std::endl;
}

// ContactBook class implementation
ContactBook::ContactBook() : curr_size(0) {
    // Initialize contacts array to nullptr
    for (unsigned int i = 0; i < MAX_SIZE; i++) {
        contacts[i] = nullptr;
    }
}
/*
ContactBook::ContactBook(ContactBook& other) : curr_size(other.curr_size) {
    // Copy only the pointers (not the actual objects)
    for (unsigned int i = 0; i < curr_size; i++) {
        contacts[i] = other.contacts[i];
    }
}

ContactBook& ContactBook::operator=(const ContactBook& other) {
    if (this != &other) {
        curr_size = other.curr_size;
        // Copy only the pointers (not the actual objects)
        for (unsigned int i = 0; i < curr_size; i++) {
            contacts[i] = other.contacts[i];
        }
    }
    return *this;
}
*/


Contact* ContactBook::Find(std::string query) {
    for (unsigned int i = 0; i < curr_size; i++) {
        if (contacts[i] && (contacts[i]->getName() == query || contacts[i]->getNumber() == query)) {
            return contacts[i];
        }
    }
    return nullptr;
}

void ContactBook::Add(Contact& contact) {
    if (curr_size < MAX_SIZE) {
        contacts[curr_size++] = &contact;
    }
}

void ContactBook::AddContacts(std::vector<Contact*> newContacts) {
    for (auto contact : newContacts) {
        if (curr_size < MAX_SIZE) {
            contacts[curr_size++] = contact;
        }
    }
}

void ContactBook::Remove(Contact& contact) {
    for (unsigned int i = 0; i < curr_size; i++) {
        if (contacts[i] == &contact) {
            for (unsigned int j = i; j < curr_size - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            curr_size--;
            return;
        }
    }
}

void ContactBook::Display() {
    for (unsigned int i = 0; i < curr_size; i++) {
        if (contacts[i]) {
            contacts[i]->display();
        }
    }
}

void ContactBook::Alphabetize() {
    std::sort(contacts, contacts + curr_size, [](Contact* a, Contact* b) {
        return a->getName() < b->getName();
    });
}

ContactBook& ContactBook::operator+=(Contact& contact) {
    Add(contact);
    return *this;
}

ContactBook& ContactBook::operator+=(ContactBook& other) {
    for (unsigned int i = 0; i < other.curr_size; i++) {
        Add(*other.contacts[i]);
    }
    return *this;
}

ContactBook ContactBook::operator+(ContactBook& other) {
    ContactBook newBook = *this;
    newBook += other;
    return newBook;
}

ContactBook& ContactBook::operator-=(Contact& contact) {
    Remove(contact);
    return *this;
}

ContactBook& ContactBook::operator-=(ContactBook& other) {
    for (unsigned int i = 0; i < other.curr_size; i++) {
        Remove(*other.contacts[i]);
    }
    return *this;
}

ContactBook ContactBook::operator-(ContactBook& other) {
    ContactBook newBook = *this;
    newBook -= other;
    return newBook;
}

bool ContactBook::operator==(ContactBook& other) {
    if (curr_size != other.curr_size) return false;
    for (unsigned int i = 0; i < curr_size; i++) {
        if (Find(contacts[i]->getName()) == nullptr) {
            return false;
        }
    }
    return true;
}

bool ContactBook::operator!=(ContactBook& other) {
    return !(*this == other);
}
