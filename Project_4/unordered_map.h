#include <iostream>
#include <string>
#include "Word_item.h" 

using namespace std;
//This file contains the hashmap implementation which is
//inspired from the lecture notes and extra web sources.

//It includes the related open addressing with linear probing functions such as
//add and search functions with their corresponding helpers.
template <typename T>
class node {
public:
    string key;
    T value;
    node<T>* next;

    node(string key, T value) {
        this->key = key;
        this->value = value;
        next = NULL;
    }

    ~node() {
        if (next) {
            delete next;
        }
    }
};

class unordered_map {
private:
    int numOfElements, capacity;
    node<Word_item*>** arr;

    int hashFunction(string key) {
        long long sum = 0, factor = 1;
        for (char ch : key) {
            sum = (sum + ch * factor) % capacity;
            factor = (factor * 31) % capacity;
        }
        return sum % capacity;
    }

    void rehash() {
        int oldCapacity = capacity;
        node<Word_item*>** oldArr = arr;

        capacity *= 2; //Always double the capacity
        arr = new node<Word_item*>*[capacity];
        for (int i = 0; i < capacity; i++) {
            arr[i] = NULL;
        }

        numOfElements = 0;
        for (int i = 0; i < oldCapacity; i++) {
            node<Word_item*>* temp = oldArr[i];
            while (temp) {
                node<Word_item*>* nextTemp = temp->next;
                temp->next = NULL;
                insertWithoutRehashing(temp->key, temp->value); //Insert without triggering rehashing
                temp = nextTemp;
            }
            oldArr[i] = nullptr;
        }
        delete[] oldArr;

        float newLoadFactor = (float)numOfElements / capacity;
        //cout << "Rehashed...\n"
        //    << "Previous table size: " << oldCapacity
        //    << ", New table size: " << capacity
        //    << ", Current unique word count: " << numOfElements
        //    << ", Current load factor: " << newLoadFactor << endl;
    }

    void insertWithoutRehashing(string key, Word_item* value) {
        int index = hashFunction(key);
        node<Word_item*>* newNode = new node<Word_item*>(key, value);
        newNode->next = arr[index];
        arr[index] = newNode;
        numOfElements++;
    }

public:
    unordered_map() {
        capacity = 10;
        numOfElements = 0;
        arr = new node<Word_item*>*[capacity];
        for (int i = 0; i < capacity; i++) {
            arr[i] = NULL;
        }
    }

    ~unordered_map() {
        for (int i = 0; i < capacity; i++) {
            delete arr[i];
        }
        delete[] arr;
    }
    //Method to get the total number of unique words
    int getUniqueWordCount() const {
        return numOfElements;
    }

    //Method to get the current load ratio
    float getCurrentLoadRatio() const {
        return static_cast<float>(numOfElements) / capacity;
    }
    void insert(string key, Word_item* value) {
        float loadFactor = (float)numOfElements / capacity;
        if (loadFactor > 0.7) {//setting load factor max limit
            rehash(); //Only increase capacity
        }

        //Insert the new value
        insertWithoutRehashing(key, value);
    }

    Word_item* search(string key) {
        int index = hashFunction(key);
        node<Word_item*>* head = arr[index];

        while (head) {
            if (head->key == key) {
                return head->value;
            }
            head = head->next;
        }
        return NULL;
    }
};
