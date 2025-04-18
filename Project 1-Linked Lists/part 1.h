//
// Created by lzy46 on 3/17/2025.
//

  #ifndef LINKEDLIST_H
  #define LINKEDLIST_H

  #include <iostream>

  template <typename T> //template class for datatype (T)
  class LinkedList {
  public:
      //Define Node strcture first
      //Make it public to allow access in main
      // i got this errors multiple times
      struct Node {

        //similar to the instruction template

          T data; //to store the value
          Node* next; //pointer to the next node in list
          Node* prev; //pointer to the previous node in list

          // an easier way to have a Constructor
          // to initialize a node with data, next, and prev(previous) pointers
          Node(const T& value, Node* nextNode = nullptr, Node* prevNode = nullptr)
              : data(value), next(nextNode), prev(prevNode) {}
      };

  private:
      // two variables
      //we need the pointers to first and last node
      Node* head; //beginning of the list
      Node* tail; //end of the list
      unsigned int nodeCount; //number of nodes in the list

  public:
      // Constructor/destructor together
      LinkedList(); //initialize an empty list
      ~LinkedList(); //delete all nodes

      // Insertion Methods
      //add information to the container
      void AddHead(const T& value); //one node at head
      void AddTail(const T& value); // one node at tail
      //multiple nodes at head
      void AddNodesHead(const T* values, unsigned int count);
      //multiple nodes at tail
      void AddNodesTail(const T* values, unsigned int count);

      // Accessor Methods
      unsigned int NodeCount() const; //return numebrs of node in list
      Node* GetHead();  // removed const keyword!!!, return pointer to first Node
      Node* GetTail();  // remove const keyword!!return pointer to second Node

      // Printing Methods
      void PrintForward() const; //print from head to tail
      void PrintReverse() const; // print from tail to head
  };


  //initialize an empty list
  template <typename T>
  LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), nodeCount(0) {}

  // delete all nodes in this list
  template <typename T>
  LinkedList<T>::~LinkedList() {
      Node* current = head; //let's start from the head
      while (current) { //loop through it!
          Node* nextNode = current->next; //we need to save the next node
          delete current; //remember we also need to delete the current node
          current = nextNode; //move on
      }
      head = tail = nullptr; //make it empty
      nodeCount = 0; //need to reset the count
  }

  // Add node at front/head
  template <typename T>
  //Create a new Node at the front of the list to store the passed in parameter.
  void LinkedList<T>::AddHead(const T& value) {
      //make a new node object pointing to old head
      Node* newNode = new Node(value, head, nullptr);
      if (head) {
          head->prev = newNode; //need to update old's head's pointer
      } else {
          tail = newNode;
          // If list was empty, tail stil points to new node
      }
      head = newNode; //now update the head to new Node
      nodeCount++; //incrementing
  }

  // Add node at the end/tail
  //Create a new Node at the end of the list to store the passed in parameter.
  //basically similar as the previous template
  template <typename T>
  void LinkedList<T>::AddTail(const T& value) {
      Node* newNode = new Node(value, nullptr, tail);
      if (tail) {
          tail->next = newNode;
      } else {
          head = newNode;
      }
      tail = newNode;
      nodeCount++;
  }

  // Add multiple nodes --- at  front
  template <typename T>
  //Given an array of values and its size,
  //insert a node for each of those at the
  //beginning list, maintaining the original order

  void LinkedList<T>::AddNodesHead(const T* values, unsigned int count) {
      for (int i = count - 1; i >= 0; --i) {  // Insert but in reverse order
          AddHead(values[i]); //call AddHead to insert each value in the list
      }
  }

  // Add multiple nodes ---- at  back
  // Ditto, except adding to the end of the list.
  template <typename T>
  void LinkedList<T>::AddNodesTail(const T* values, unsigned int count) {
      for (unsigned int i = 0; i < count; ++i) {
          AddTail(values[i]);
      }
  }

  // return the number of nodes in the list
  // how many things are stored in this list?
  template <typename T>
  unsigned int LinkedList<T>::NodeCount() const {
      return nodeCount;
  }

  // get pointer to the head node
  // Returns the head pointer. Const and non-const versions
  template <typename T>
  typename LinkedList<T>::Node* LinkedList<T>::GetHead() {
      return head; //the first node
  }

  // get pointer to the tail node
  // Returns the tail pointer. Const and non-const versions
  template <typename T>
  typename LinkedList<T>::Node* LinkedList<T>::GetTail() {
      return tail; //return the pointer to last node
  }

  // print list from head to tail
  //Iterator through all of the nodes
  //and print out their values, one a time.
  template <typename T>
  void LinkedList<T>::PrintForward() const {
      Node* current = head; //start from head
      while (current) {  // iterate until nullptr
          std::cout << current->data << " ";  // //print data
          //debug: make sure data is used/formatted correctly
          current = current->next; //move on
      }
      std::cout << std::endl;
  }

  // print list from tail to head
  //Exactly the same as PrintForward
  //except completely the opposite
  template <typename T>
  void LinkedList<T>::PrintReverse() const {
      Node* current = tail;
      while (current) {
          std::cout << current->data << " ";
          current = current->prev;
      }
      std::cout << std::endl;
  }

  #endif // LinkedList.h
