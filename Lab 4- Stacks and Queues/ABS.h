//
// Created by lzy46 on 3/17/2025.
//

#ifndef ABS_H
#define ABS_H

//define a generic stack class
//define the template-- implement all constructors
//--copy assignments operator
//--destructor --release the memory address
//---push/pop operation (increasing/decreasing)
//---peek -- check if it is empty
//---also resizing the stack
//---implement all methods

#include <stdexcept> // For std::runtime_error
//in case of errors from empty stack
template <typename T> //template starts here
class ABS {
private:
    T* data;                // A pointer that holds the stacl elements
    unsigned int capacity;  // Maximum capacity of the stack can store
    unsigned int size;      // number of elements in the stack (current/updated)
    float scaleFactor;      //  A factor used for
    //resizing the stack (default value is 2.0).


    // here's all functions that might help:
    //adjusts the size of the allocated array.
    //increase parameter is a boolean type
    void resize(bool increase) {
        unsigned int newCapacity; //new size
        if (increase) {
            newCapacity = capacity * scaleFactor;
            // multiply capacity by scaleFactor if true
        } else {
            newCapacity = capacity / scaleFactor;
            // divide capacity by scaleFactor if false
        }

        T* newData = new T[newCapacity];
        // Allocate a new array with the new capacity
        //hold the stack's element
        for (unsigned int i = 0; i < size; ++i) {
            newData[i] = data[i];
            // Copy existing elements
            // to the new array for the new size

        }

        delete[] data; // Free the memory of old array
        data = newData; // assign the pointer to the new array
        capacity = newCapacity; // Update stack's capacity
    }

public:
    // Default constructor
    ABS() : capacity(1), size(0), scaleFactor(2.0f) {
        data = new T[capacity];
        // Initialize array with default capacity
        //to hold one element
    }

    // Constructor with a specified initial capacity
    ABS(int initialCapacity) : capacity(initialCapacity), size(0), scaleFactor(2.0f) {
        if (initialCapacity <= 0) {
          //it has to be non-negative
            throw std::runtime_error("Capacity must be greater than 0.");
        }
        data = new T[capacity];
        // Initialize array with specified capacity
        //allocates the memory also
    }

    // Copy constructor & deep copy
    // other is the stack object we are copying from
    //passing a constant reference (don't modify)
    ABS(const ABS& other) : capacity(other.capacity), size(other.size), scaleFactor(other.scaleFactor) {
        data = new T[capacity]; // Allocate new array
        for (unsigned int i = 0; i < size; ++i) {
            data[i] = other.data[i]; // Copy elements from the other stack
        }
    }

    // Copy assignment operator
    ABS& operator=(const ABS& other) {
        if (this != &other) { // Check for objects
            delete[] data; // Free the old data array

            capacity = other.capacity;
            size = other.size;
            scaleFactor = other.scaleFactor;

            data = new T[capacity]; // Allocate new array as before
            for (unsigned int i = 0; i < size; ++i) {
                data[i] = other.data[i]; // Copy elements from the other stack
            }
        }
        return *this;
    }

    // Destructor when stack obj is destroyed
    ~ABS() {
        delete[] data; // Free the memory from data array
    }

    // Push an element onto the stack
    //add 1 element on top of the stack
    void push(T value) {
        if (size == capacity) {
            resize(true); // Resize the stack if it's full
        }
        data[size++] = value; // Add the element and increase the size
    }

    // Pop an element from the stack
    T pop() {
        if (size == 0) {
          //exception
            throw std::runtime_error("Cannot pop from an empty stack.");
        }
          //remove the top element
        T value = data[--size];

        // Resize the stack
        //if it's less than 1/scaleFactor full
        //too empty
        //it shrinks
        if (size < capacity / scaleFactor) {
            resize(false);
        }

        return value;
    }

    // Return the top element (without removing it)
    T peek() const {
        if (size == 0) {
            throw std::runtime_error("Cannot peek an empty stack.");
        }
        return data[size - 1];
    }
    //now return all varibles we listed before
    // Get the current number of elements in the stack
    unsigned int getSize() const {
        return size;
    }

    // Get the maximum capacity of the stack
    unsigned int getMaxCapacity() const {
        return capacity;
    }

    // Get the underlying array (return a pointer to that)

};

#endif // ABS_H
