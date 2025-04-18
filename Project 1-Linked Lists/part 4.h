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
    //same as part 1 2 3
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
    unsigned int nodeCount;

public:
    LinkedList() : head(nullptr), tail(nullptr), nodeCount(0) {}

    ~LinkedList()
    {
        Clear();
    }

    // add a new node to the head
    // same as before..
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
    // same as before..
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

    // same as before..
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

    // Removes the first node with the specified value
    // Remove ALL Nodes containing values matching that of the
    //passed-in Returns how many instances were removed
    int Remove(const T &value)
    {
        int count = 0;
        Node *current = head;

        while (current != nullptr)
        {
            Node *toDelete = current;
            current = current->next; // move the pointer
            //very very important
            //move to the next node before delete anything

            if (toDelete->data == value)
            {
                if (toDelete->prev)
                    toDelete->prev->next = toDelete->next;
                else
                    head = toDelete->next; //update the head!

                if (toDelete->next)
                    toDelete->next->prev = toDelete->prev;
                else
                    tail = toDelete->prev;//update the tail!

                delete toDelete;
                nodeCount--; //decrement nodeCount
                count++;
            }
        }
        return count;
    }

    // Removes the head node
    // Deletes the first Node in the list
    //Returns whether or not the Node was removed.
    bool RemoveHead()
    {
        if (head == nullptr)
            return false;

        Node *toDelete = head; //need to store the tail node to delete
        if (head->next)
            head->next->prev = nullptr;
        head = head->next;
        if (head == nullptr)
            tail = nullptr;

        delete toDelete;
        nodeCount--;
        return true;
    }

    // Removes the tail node
    // Deletes the last Node, returning
    //whether or not the operation was successful.
    //very similar to revove head
    bool RemoveTail()
    {
        if (tail == nullptr)
            return false;

        Node *toDelete = tail;
        if (tail->prev)
            tail->prev->next = nullptr;
        tail = tail->prev;
        if (tail == nullptr)
            head = nullptr;

        delete toDelete;
        nodeCount--;
        return true;
    }

    // Removes a node at a specific index
    //Deletes the index-th Node from the list,
    //returning whether or not the operation
    //was successful.
    bool RemoveAt(unsigned int index)
    {
        if (index >= nodeCount)
            return false; //out of bound

        Node *current = head;
        for (unsigned int i = 0; i < index; ++i)
        {
            current = current->next;
            //traverse to the node at given index
        }

        if (current == head)
            return RemoveHead(); //basically call 2 functins before
        if (current == tail)
            return RemoveTail();

        //what if the ndoe is in the middle?
        //then update the surrounding!
        if (current->prev)
            current->prev->next = current->next;
        if (current->next)
            current->next->prev = current->prev;

        delete current;
        nodeCount--;
        return true;
    }

    // Clears the ENTIRE list

    void Clear()
    {
        Node *current = head;
        while (current != nullptr)
        {
            Node *toDelete = current;
            current = current->next;
            delete toDelete;
        }
        //reset both
        head = tail = nullptr;
        nodeCount = 0;
    }

    // prints the list from head to tail
    //same as before
    void PrintForward() const
    {
        Node *current = head;
        while (current != nullptr)
        {
            cout << current->data << endl;
            current = current->next;
        }
    }

    // Recursive Print Functions
    //This function MUST be implemented using
    //recursion
    void PrintForwardRecursive() const
    {
        PrintForwardRecursive(head);
        cout << endl;
    }

    // Prints the list forward using recursion
    void PrintForwardRecursive(Node *node) const
    {
        if (node == nullptr)
            return; //base case: stop when it's null
        cout << node->data << endl;
        PrintForwardRecursive(node->next); //recursion
    }

    // very similar to the above
    void PrintReverseRecursive() const
    {
        PrintReverseRecursive(tail);
        cout << endl;
    }

    // almost the most
    void PrintReverseRecursive(Node *node) const
    {
        if (node == nullptr)
            return;
        cout << node->data << endl;
        PrintReverseRecursive(node->prev);
    }

    // return the number of node in list
    unsigned int NodeCount() const { return nodeCount; }

    // Overloading the equality operator
    // Just copy the code from part 3
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

    // accessor methods for head and tail
    //they were used in clear() function test
    Node* GetHead() const { return head; }
    Node* GetTail() const { return tail; }
};

#endif // LINKEDLIST_H
