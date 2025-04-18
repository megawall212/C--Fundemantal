//
// Created by lzy46 on 3/17/2025.
//

#ifndef ABQ_H
#define ABQ_H

#include <stdexcept>

template <typename T>

//same thing: we start a template here
class ABQ {
private:
    //get all the private variables required
    T* data;                // Dynamically allocated array to store queue elements
    unsigned int capacity;  // Maximum capacity of the queue this time
    unsigned int size;      // updated  number of elements in the queue
    unsigned int front;     // Index of the front element in the queue
    //also the first to be dequeued
    unsigned int back;      // Index where the next element will be added
    //also last inserted
    // different from stack
    float scaleFactor;      // Scaling factor for resizing the queue (2.0f)

    // Helper function to resize the queue
    void resize(bool increase) {
        unsigned int newCapacity;
        if (increase) {
            newCapacity = capacity * scaleFactor;

        } else {
            newCapacity = capacity / scaleFactor;
            // increase/decrease the capacity by scaleFactor
            //same as stack
        }

        T* newData = new T[newCapacity];
        //A new array is allocated with updated capacity

        // Copy elements into the new arrays
        //for loop
        //modular arthimetic / circular nature
        for (unsigned int i = 0; i < size; ++i) {
          //if it exceeds the capacity it wraps back to the
          //beginnning
            newData[i] = data[(front + i) % capacity];
        }
        // then do the same thing in part 1
        delete[] data;
        data = newData;
        capacity = newCapacity; // Update capacity
        front = 0; // Reset front to the start of the new array
        //basically make it to index 0
        back = size; // Reset back to the end of the copied elements
        //which is also the next available element
    }

public:
    // Default constructor
    ABQ() : capacity(1), size(0), front(0), back(0), scaleFactor(2.0f) {
        data = new T[capacity];
        // Initialize array with default capacity of 1
        //and a size of 0
        //allocates memory with initial capacity

    }

    // Constructor with specified initial capacity
    ABQ(int initialCapacity) : capacity(initialCapacity), size(0), front(0), back(0), scaleFactor(2.0f) {
        if (initialCapacity <= 0) {
          // remember it can't be negative
            throw std::runtime_error("Capacity must be greater than 0.");
        }
        data = new T[capacity];
        // specify the initial capacity of the queue
    }

    // Copy constructor
    // allocates memory for the new data
    //and copies elements from the other quene
    //same idea as before
    ABQ(const ABQ& other) : capacity(other.capacity), size(other.size), front(other.front), back(other.back), scaleFactor(other.scaleFactor) {
        data = new T[capacity];
        for (unsigned int i = 0; i < size; ++i) {
            data[i] = other.data[(other.front + i) % other.capacity];
            // Copy elements from the other queue
        }
    }

    // Copy assignment operator
    // we want to copy the value from the "other" to
    //current project
    ABQ& operator=(const ABQ& other) {
        if (this != &other) { // Check for self-assignment
            delete[] data; // Free existing array

            capacity = other.capacity;
            size = other.size;
            front = other.front;
            back = other.back;
            scaleFactor = other.scaleFactor;

            data = new T[capacity]; // Allocate new array
            //using same method
            for (unsigned int i = 0; i < size; ++i) {
                data[i] = other.data[(other.front + i) % other.capacity]; // Copy elements from the other queue
            }
        }
        return *this;
    }

    // Destructor
    ~ABQ() {
        delete[] data; // Free the memory
    }

    // Enqueue an element into the queue
    //in other words: add an element to the back of this quene
    void enqueue(T value) {
        if (size == capacity) {
            resize(true); // Resize the queue if it's full
        }
        data[back] = value; // Add the element at the back
        back = (back + 1) % capacity; // Move back index circularly
        size++; // Increment size
    }

    // Dequeue an element from the queue
    // Removes and returns the element at the front of the queue

    T dequeue() {
        if (size == 0) {
            throw std::runtime_error("Cannot dequeue from an empty queue.");
        }

        T value = data[front];
        front = (front + 1) % capacity; // Move front index
        size--; // decrease size


        if (size < capacity / scaleFactor) {
            resize(false);
        }

        return value;
    }

    // Peek: returns the front element without removing it

    T peek() const {
        if (size == 0) {
            throw std::runtime_error("Cannot peek an empty queue.");
        }
        return data[front];
    }

    // Get the current number of elements
    unsigned int getSize() const {
        return size;
    }

    // Get the maximum capacity of the queue
    unsigned int getMaxCapacity() const {
        return capacity;
    }


};

#endif // ABQ_H