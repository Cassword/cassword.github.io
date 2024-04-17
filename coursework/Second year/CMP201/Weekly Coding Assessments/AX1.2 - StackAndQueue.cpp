
#include <iostream>
#include "StackAndQueue.h"

// Default constructor, init array
ArrayStack::ArrayStack()
{
    arr = new int[capacity];
}

// Remove first element, return value.
int ArrayStack::Pop()
{
    int n = arr[stackTop]; 
    stackTop--;
    return n;
}

// Check first element, return value.
int ArrayStack::Peek()
{
    int n = arr[stackTop]; 
    return n;
}

// Add element to top of stack, 
// calls DoubleArray() where appropriate
void ArrayStack::Push(int n)
{
    if (stackTop == capacity - 1) {
        DoubleArray();
    }
    stackTop++;
    arr[stackTop] = n;
}

// Print elements in Stack neatly
// DO NOT CHANGE: used for testing and assessment
void ArrayStack::Display()
{
    std::cout << arr[0] << "\t<- head" << std::endl;
    for (int i = 1; i < stackTop + 1; i++)
    {
        std::cout << arr[i] << std::endl;
    }
}

// Updates array pointer to new array of double the size
// elements are copied in from old array with position preserved.
void ArrayStack::DoubleArray()
{
    capacity *= 2;
    int* new_arr = new int[capacity];
    for (int i = 0; i < stackTop + 1; i++)
    {
        new_arr[i] = arr[i];
    }
    arr = new_arr;
}

// Node constructor
Node::Node(int n)
{
    next = nullptr;
    data = n;
}

// QL constructor
QueueList::QueueList()
{
    front = nullptr;
    back = nullptr;

}

// Add item to back of queue
void QueueList::Enqueue(int n)
{
    Node* nextVal = new Node(n);
    if (!front && !back) {
        front = nextVal;
        back = nextVal;
    }
    else {
        back->next = nextVal;
        back = nextVal;
    }
}

// Remove item from front of queue
int QueueList::Dequeue()
{
    Node* temp = front;
    if (!front && !back) {
        return NULL;
    }
    else if (front == back) {
        back = nullptr;
        front = nullptr;
        return temp->data;
    }
    else {
        front = front->next;
        return temp->data;
    }
}


// Print elements in Stack neatly
// DO NOT CHANGE: used for testing and assessment
void QueueList::Display()
{
    if (!front)
    {
        std::cout << "[]";
        return;
    }
    Node* n = front;
    std::cout << "f: ";
    while (n != back)
    {
        std::cout << n->data << ",\t";
        n = n->next;
    }
    std::cout << "b: " << n->data << std::endl;
}

