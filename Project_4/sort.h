#pragma once
#include "Word_item.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

void insertionSort(vector<Word_item>& items);
void heapSort(vector<Word_item>& items);

// Quick Sort with the first element as pivot
void quickSortFirst(vector<Word_item>& items, int low, int high);

// Quick Sort with a random element as pivot
void quickSortRandom(vector<Word_item>& items, int low, int high);

// Quick Sort with the median of three as pivot
void quickSortMedian(vector<Word_item>& items, int low, int high);

// Merge Sort (In-place)
void mergeSort(vector<Word_item>& items, int l, int r);
