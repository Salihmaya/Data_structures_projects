#include "Stack.h"
#include <iostream>
using namespace std;

template<typename T>
Stack<T>::Stack() : topNode(nullptr), size(0) {}

template <typename T>
Stack<T>::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

template <typename T>
void Stack<T>::push(const T& value) {
    Node<T>* newNodePtr = new Node<T>(value, topNode);
    topNode = newNodePtr;
    size++;
}

template <typename T>
bool Stack<T>::pop() {
    if (isEmpty()) {
        // You can throw an exception here if you prefer
        return false;
    }
    Node<T>* temp = topNode;
    topNode = topNode->next;
    delete temp;
    size--;
    return true;
}

template <typename T>
bool Stack<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
T Stack<T>::top() const {
    if (isEmpty()) {
        cout << "Error: Stack is empty";
    }
    return topNode->data;
}

