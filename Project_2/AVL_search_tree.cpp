#include "AVL_search_Tree.h"


// A utility function to get the height of the tree
template<class Key, class Value>
int AVLSearchTree<Key, Value>::height(Node* N) {
    if (N == nullptr)
        return 0;
    return N->height;
}

// A utility function to right rotate subtree rooted with y
template<class Key, class Value>
typename AVLSearchTree<Key, Value>::Node* AVLSearchTree<Key, Value>::rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights, then return new node
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    return x;
}

// A utility function to left rotate subtree rooted with x
template<class Key, class Value>
typename AVLSearchTree<Key, Value>::Node* AVLSearchTree<Key, Value>::leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights, then return new nood
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    return y;
}

// Get Balance factor of node N
template<class Key, class Value>
int AVLSearchTree<Key, Value>::getBalance(Node* N) {
    if (N == nullptr)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key in the subtree rooted with node
// and returns the new root of the subtree.
template<class Key, class Value>
typename AVLSearchTree<Key, Value>::Node* AVLSearchTree<Key, Value>::insert(Node* node, const Key& key, const Value& value) {
    // First Perform the normal BST insertion
    if (node == nullptr)
        return (newNode(key, value));

    if (key < node->key)
        node->left = insert(node->left, key, value);
    else if (key > node->key)
        node->right = insert(node->right, key, value);
    else // Equal keys not allowed
        return node;

    // Update height of this ancestor node
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // return the (unchanged) node pointer
    return node;
}


//Node deleting function of the tree, the returning a message in case the input to be removed
//does not exist performed in main cpp (ksalih_etc)
template <class Key, class Value>
typename AVLSearchTree<Key, Value>::Node* AVLSearchTree<Key, Value>::deleteNode(Node* root, const Key& key) {
    // First PERFORM STANDARD BST DELETE
    if (root == nullptr) {
        return root;
    }

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    }
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    }
    // if key is same as root's key, then this is the node to be deleted
    else {
        // node with only one child or no child
        if (root->left == nullptr || root->right == nullptr) {
            Node* temp = root->left ? root->left : root->right;

            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else { // One child case
                *root = *temp; // Copy the contents of the non-empty child
            }
            delete temp;
        }
        else {
            // Node with two children: Get the inorder successor (smallest
            // in the right subtree)
            Node* temp = minValueNode(root->right);

            // Copy the inorder successor's data to this node
            root->key = temp->key;
            root->value = temp->value;

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node then return
    if (root == nullptr) {
        return root;
    }

    // THEN UPDATE HEIGHT OF THE CURRENT NODE
    root->height = 1 + std::max(height(root->left), height(root->right));

    // GET THE BALANCE FACTOR OF THE NODE
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Utility function to find the node with minimum key value
template <class Key, class Value>
typename AVLSearchTree<Key, Value>::Node* AVLSearchTree<Key, Value>::minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

//This function is utilized to search through the tree and return null if its not found
template <class Key, class Value>
Value AVLSearchTree<Key, Value>::search(const Key& key) {
    Node* current = root;
    while (current != nullptr) {
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else
            return current->value; // key found
    }
    return nullptr; // key not found
}