#pragma once

#include "Word_item.h" 
#include <algorithm>

template <class Key, class Value>
class AVLSearchTree {
public:
    AVLSearchTree() : root(nullptr) {}
    void insert(const Key& key, const Value& value) {
        root = insert(root, key, value);
    }

    void remove(const Key& key) {
        root = deleteNode(root, key);
    }

    Value publicSearch(const Key& key) {
        return search(key);
    }
private:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;
        int height;

        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    // Private helper methods
    Node* newNode(const Key& key, const Value& value) {
        return new Node(key, value);
    }
    int height(Node* N);
    Node* rightRotate(Node* y);
    Node* leftRotate(Node* x);
    int getBalance(Node* N);
    Node* insert(Node* node, const Key& key, const Value& value);

    // deleteNode functions
    Node* deleteNode(Node* root, const Key& key);
    Node* minValueNode(Node* node);

    //search functions
    Value search(const Key& key);
};

// Include the implementation file
#include "AVL_search_Tree.cpp"
