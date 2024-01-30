#pragma once

#include "Word_item.h"
#include <algorithm>

//BASIC BINARY SEARCH TREE FUNCTIONS SUCH AS INSERT REMOVE ETC.

template <class Key, class Value>
class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    void insert(const Key& key, const Value& value) {
        root = insertInternal(root, key, value);
    }

    void remove(const Key& key) {
        root = deleteNode(root, key);
    }

    Value publicSearch(const Key& key) {
        return search(root, key);
    }
    void insertIterative(const Key& key, Value value) {
        if (root == nullptr) {
            root = new Node(key, value);
            return;
        }

        Node* current = root;
        while (true) {
            if (key < current->key) {
                if (current->left == nullptr) {
                    current->left = new Node(key, value);
                    break;
                }
                else {
                    current = current->left;
                }
            }
            else if (key > current->key) {
                if (current->right == nullptr) {
                    current->right = new Node(key, value);
                    break;
                }
                else {
                    current = current->right;
                }
            }
            else {
                break;
            }
        }
    }
private:
    struct Node {
        Key key;
        Value value;
        Node* left;
        Node* right;

        Node(Key k, Value v) : key(k), value(v), left(nullptr), right(nullptr) {}
    };

    Node* root;

    //This insertion added to prevent overflow for some cases such as 3
    Node* insertInternal(Node* node, const Key& key, const Value& value) {
        if (node == nullptr) {
            return new Node(key, value);
        }

        if (key < node->key) {
            node->left = insertInternal(node->left, key, value);
        }
        else if (key > node->key) {
            node->right = insertInternal(node->right, key, value);
        }

        return node;
    }

    Node* deleteNode(Node* node, const Key& key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = deleteNode(node->left, key);
        }
        else if (key > node->key) {
            node->right = deleteNode(node->right, key);
        }
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = minValueNode(node->right);
            node->key = temp->key;
            node->value = temp->value;
            node->right = deleteNode(node->right, temp->key);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Value search(Node* node, const Key& key) {
        if (node == nullptr) {
            return nullptr;
        }

        if (key < node->key) {
            return search(node->left, key);
        }
        else if (key > node->key) {
            return search(node->right, key);
        }
        else {
            return node->value;
        }
    }
};
