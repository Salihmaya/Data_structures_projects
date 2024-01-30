#pragma once

template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
    Node(T val, Node* nxt) : data(val), next(nxt) {}
};

template <typename T>
class Stack {
private:
    Node<T>* topNode;
    int size;

public:
    Stack();
    ~Stack();
    void push(const T& value);
    bool pop();
    T top() const;
    bool isEmpty() const;
};

// Include the implementation here since it's a template
#include "Stack.cpp"
