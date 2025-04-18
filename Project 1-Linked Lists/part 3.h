//
// Created by lzy46 on 3/17/2025.
//

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

template <typename T>
class LinkedList
{
public:
    // node structure for LinkedList
    struct Node
    {
      // same variable for all 4 parts
      //data stored; pointers for previous and next node
        T data;
        Node *prev;
        Node *next;
        //initialize
        Node(const T &data) : data(data), prev(nullptr), next(nullptr) {}
    };

private:
    Node *head;
    Node *tail;
    unsigned int nodeCount;  //numbers of node in this LinkedList

public:
    LinkedList() : head(nullptr), tail(nullptr), nodeCount(0) {}

    //destructor
    //free memory
    ~LinkedList()
    {
        Clear();
    }

    // Adds a new node to the head pf this list
    void AddHead(const T &data)
    {
        Node *newNode = new Node(data);
        if (head == nullptr)
        {
            head = tail = newNode; //only if the list is empty
            //we then set the head and tail to new node
        }
        else
        {
            newNode->next = head; //new node points
            head->prev = newNode;
            head = newNode;  //need to update the head
        }
        nodeCount++;
    }

    // Adds a new node to the tail
    //we did it before
    //so no comment
    void AddTail(const T &data)
    {
        Node *newNode = new Node(data);
        if (tail == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        nodeCount++;
    }

    // Finds a node with a specific value
    //we did it before
    //so no comment
    Node *Find(const T &value)
    {
        Node *current = head;
        while (current != nullptr)
        {
            if (current->data == value)
                return current;
            current = current->next;
        }
        return nullptr;
    }


    // Insert the new node before the indicated node
    void InsertBefore(Node *node, const T &value)
    {
        if (node == nullptr)
            return; // chill if the node has nothing

        Node *newNode = new Node(value); //create a new node
        newNode->prev = node->prev;  //points to the give
        newNode->next = node;   //newNode's next object points to the given node


        if (node->prev)
            node->prev->next = newNode; //update to the new node
        node->prev = newNode;

        if (node == head) //if the given node is head
            head = newNode; //update the head to new node

        nodeCount++;
    }

    // Inserts a node after the given node
    //(create a new node to store the passed in value)
    //same ideas but with tail this time
    void InsertAfter(Node *node, const T &value)
    {
        if (node == nullptr)
            return;

        Node *newNode = new Node(value);
        newNode->next = node->next;
        newNode->prev = node;

        if (node->next)
            node->next->prev = newNode;
        node->next = newNode;

        if (node == tail)
            tail = newNode;

        nodeCount++;
    }

    // Inserts a node at a specific index
    // Inserts a new Node to store the first parameter
    //at the index-th location.
    void InsertAt(const T &value, unsigned int index)
    {
        if (index > nodeCount)
            return; //chill of it's out of bound

        if (index == 0)
        {
            AddHead(value); //insert at head if it's 0
            return;
        }

        if (index == nodeCount) //well that means it's at the end
        {
            AddTail(value); // insert at tail!
            return;
        }

        Node *current = head;
        for (unsigned int i = 0; i < index; ++i)
        {
          //insert new ndoe before the current node
            current = current->next;
        }

        InsertBefore(current, value);
    }

    // Returns number of nodes in this list
    unsigned int NodeCount() const { return nodeCount; }

    // clean it
    //free all nodes
    void Clear()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *toDelete = current;
            current = current->next;
            delete toDelete;
        }
        //reset everything
        head = tail = nullptr;
        nodeCount = 0;
    }

    // Prints the list from head to tail
    // it's really tricky
    //be careful about endl.....
    void PrintForward() const
    {
        Node *current = head;
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    // Overloading the equality operator
    // need to compare two linked lists
    //basically if they are different or have different data
    //then they are not equal
    bool operator==(const LinkedList &other) const
    {
        if (nodeCount != other.nodeCount)
            return false;

        Node *current = head;
        Node *otherCurrent = other.head;
        while (current != nullptr)
        {
            if (current->data != otherCurrent->data)
                return false;
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
        return true;
    }
};
//it is not ideal but i just reuse it ...
//but my code is identical
//so there;s no syntax or compilier errors fortunately
#endif // LINKEDLIST_H
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
using namespace std;

template <typename T>
class LinkedList
{
public:
    // Node structure
    struct Node
    {
        T data;
        Node *prev;
        Node *next;
        Node(const T &data) : data(data), prev(nullptr), next(nullptr) {}
    };

private:
    Node *head;
    Node *tail;
    unsigned int nodeCount;  // Count of nodes in the list

public:
    LinkedList() : head(nullptr), tail(nullptr), nodeCount(0) {}

    ~LinkedList()
    {
        Clear();
    }

    // Adds a new node to the head
    void AddHead(const T &data)
    {
        Node *newNode = new Node(data);
        if (head == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        nodeCount++;
    }

    // Adds a new node to the tail
    void AddTail(const T &data)
    {
        Node *newNode = new Node(data);
        if (tail == nullptr)
        {
            head = tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
        nodeCount++;
    }

    // Finds a node with a specific value
    Node *Find(const T &value)
    {
        Node *current = head;
        while (current != nullptr)
        {
            if (current->data == value)
                return current;
            current = current->next;
        }
        return nullptr;
    }

    // Inserts a node before the given node
    void InsertBefore(Node *node, const T &value)
    {
        if (node == nullptr)
            return;

        Node *newNode = new Node(value);
        newNode->prev = node->prev;
        newNode->next = node;

        if (node->prev)
            node->prev->next = newNode;
        node->prev = newNode;

        if (node == head)
            head = newNode;

        nodeCount++;
    }

    // Inserts a node after the given node
    void InsertAfter(Node *node, const T &value)
    {
        if (node == nullptr)
            return;

        Node *newNode = new Node(value);
        newNode->next = node->next;
        newNode->prev = node;

        if (node->next)
            node->next->prev = newNode;
        node->next = newNode;

        if (node == tail)
            tail = newNode;

        nodeCount++;
    }

    // Inserts a node at a specific index
    void InsertAt(const T &value, unsigned int index)
    {
        if (index > nodeCount)
            return;

        if (index == 0)
        {
            AddHead(value);
            return;
        }

        if (index == nodeCount)
        {
            AddTail(value);
            return;
        }

        Node *current = head;
        for (unsigned int i = 0; i < index; ++i)
        {
            current = current->next;
        }

        InsertBefore(current, value);
    }

    // return
    unsigned int NodeCount() const { return nodeCount; }


    void Clear()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head = tail = nullptr;
        nodeCount = 0;
    }

    // Prints the list from head to tail
    void PrintForward() const
    {
        Node *current = head;
        while (current != nullptr)
        {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }


    bool operator==(const LinkedList &other) const
    {
        if (nodeCount != other.nodeCount)
            return false;

        Node *current = head;
        Node *otherCurrent = other.head;
        while (current != nullptr)
        {
            if (current->data != otherCurrent->data)
                return false;
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
        return true;
    }
};

#endif // LINKEDLIST_H
