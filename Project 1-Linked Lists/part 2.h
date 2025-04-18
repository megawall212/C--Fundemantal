//
// Created by lzy46 on 3/17/2025.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdexcept>
#include <vector>
//most of the comments are at the second part of this code if we scroll down more
using namespace std;

template <typename T>
//same as part 1
//tired of making comments
class LinkedList {
public:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        //Node Constructor
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };
    //default Constructor
    LinkedList() : head(nullptr), tail(nullptr), nodeCount(0) {}
    ~LinkedList();
    LinkedList(const LinkedList<T>& other);  // Copy Constructor
    LinkedList<T>& operator=(const LinkedList<T>& other);  // Copy Assignment Operator

    void AddHead(const T& value);
    void AddTail(const T& value);
    void PrintForward() const;

    Node* GetNode(unsigned int index) const;
    Node* Find(const T& value) const;
    void FindAll(std::vector<Node*>& nodes, const T& value) const;

    // Overloads [] to access elements by index
    // Takes an index, and returns data from the indexth
    //node
    T& operator[](unsigned int index);

private:
    Node* head;
    Node* tail;
    unsigned int nodeCount;

    void Clear();
    void CopyList(const LinkedList<T>& other);  // Helper function to copy a list
};

// Copy Constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), nodeCount(0) {
    CopyList(other);
}

// Copy Assignment Operator
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this != &other) {  // Check for self-assignment
        Clear();  // Delete the current list
        CopyList(other);  // Copy the other list
    }
    return *this;
}

// Helper function to copy a list
template <typename T>
void LinkedList<T>::CopyList(const LinkedList<T>& other) {
    Node* current = other.head;
    while (current != nullptr) {
        AddTail(current->data);  // Add data to the tail of the current list
        current = current->next;
    }
}

template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
    if (index >= nodeCount) {
        throw out_of_range("Index out of range");
    }

    Node* node = GetNode(index);
    return node->data;
}

template <typename T>
void LinkedList<T>::AddHead(const T& value) {
    Node* newNode = new Node(value);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    nodeCount++;
}

template <typename T>
void LinkedList<T>::AddTail(const T& value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    nodeCount++;
}

template <typename T>
void LinkedList<T>::PrintForward() const {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
    if (index >= nodeCount) {
        throw out_of_range("Index out of range");
    }

    Node* current = head;
    for (unsigned int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current;
}

template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

template <typename T>
void LinkedList<T>::FindAll(std::vector<Node*>& nodes, const T& value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            nodes.push_back(current);
        }
        current = current->next;
    }
}

template <typename T>
LinkedList<T>::~LinkedList() {
    Clear();
}

template <typename T>
void LinkedList<T>::Clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = tail = nullptr;
    nodeCount = 0;
}

#endif // LINKEDLIST_H
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <stdexcept>
#include <vector>
//it is not ideal but i just reuse it ...
//but my code is identical
//so there;s no syntax or complier errors fortunately

using namespace std;

template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* next;
        Node* prev;
        //Node consstructor
        Node(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    LinkedList() : head(nullptr), tail(nullptr), nodeCount(0) {}
    ~LinkedList();
    LinkedList(const LinkedList<T>& other);  // Copy Constructor
    LinkedList<T>& operator=(const LinkedList<T>& other);  // Copy Assignment Operator

    //3 functions that we did in part 1
    void AddHead(const T& value);
    void AddTail(const T& value);
    void PrintForward() const;

    //Given an index, return a pointer to the node at that index.
    //basically retrieves a node at a given index

    Node* GetNode(unsigned int index) const;
    Node* Find(const T& value) const;  //// Finds a node with a specific value
    void FindAll(std::vector<Node*>& nodes, const T& value) const; //find all nodes and store a pointer

    T& operator[](unsigned int index);    // Overloads [] to access elements by index

private:
    Node* head;
    Node* tail;
    unsigned int nodeCount; //the number of nodes

    void Clear(); //delete nodes
    void CopyList(const LinkedList<T>& other);  // function to copy a list (stackoverflow)
};

// Copy Constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), nodeCount(0) {
    CopyList(other); //Copies nodes from another list
}

// Copy Assignment Operator
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& other) {
    if (this != &other) {  // Check for self-assignment (prevent it!)
        Clear();  // Delete the current list
        CopyList(other);  // And copy the other list
    }
    return *this;
}

// copy a list
template <typename T>
void LinkedList<T>::CopyList(const LinkedList<T>& other) {
    Node* current = other.head;
    while (current != nullptr) {
        AddTail(current->data);  // Add data to the tail of the current list
        //basically add/assign each node to the tail
        current = current->next;
    }
}
// Overloaded [] operator
template <typename T>
T& LinkedList<T>::operator[](unsigned int index) {
    if (index >= nodeCount) {
        throw out_of_range("Index out of range"); //print smth
    }

    Node* node = GetNode(index);
    return node->data; // get the node and return data
}

template <typename T>
// add a node at the beginning(head)
void LinkedList<T>::AddHead(const T& value) {
    Node* newNode = new Node(value);
    if (head == nullptr) { //if we have an empty list
        head = tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    nodeCount++;
}
// add a node at the end(tail)
template <typename T>
void LinkedList<T>::AddTail(const T& value) {
    Node* newNode = new Node(value);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    nodeCount++;
}
// print the list fowards
template <typename T>
void LinkedList<T>::PrintForward() const {
    Node* current = head;
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

//Given an index, return a pointer to the node at that index.
//basically retrieves a node at a given index
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const {
    if (index >= nodeCount) {
        throw out_of_range("Index out of range");
    }

    Node* current = head;
    for (unsigned int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current;
}
// finds the first node containing the given value
//Find the first node with a data value matching the passed in parameter
//returning a pointer to that node
//Returns nullptr if no matching node found
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Find(const T& value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            return current; //return the first ! it matches
        }
        current = current->next;
    }
    return nullptr;
}
// finds all nodes containing a specific value
// and store a pointer to that node in the passed in vector.
template <typename T>
void LinkedList<T>::FindAll(std::vector<Node*>& nodes, const T& value) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
            nodes.push_back(current);
        }
        current = current->next;
    }
}

template <typename T> //destructor
LinkedList<T>::~LinkedList() {
    Clear(); //clear the list

}
// Deletes all Nodes.
//Don’t forget the node count—how after you deleted all of them
template <typename T>
void LinkedList<T>::Clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp; // debug: need to free memory!
    }
    head = tail = nullptr;
    nodeCount = 0;
}

#endif // LINKEDLIST_H

