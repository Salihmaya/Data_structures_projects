#include "sort.h"

using namespace std;
//Insertion sort
void insertionSort(vector<Word_item>& items) {
    int i, j;
    Word_item key;
    for (i = 1; i < items.size(); i++) {
        key = items[i];
        j = i - 1;

        while (j >= 0 && items[j].word > key.word) {
            items[j + 1] = items[j];
            j = j - 1;
        }
        items[j + 1] = key;
    }
}
//for heapsort
void heapify(vector<Word_item>& items, int N, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < N && items[l].word > items[largest].word)
        largest = l;

    if (r < N && items[r].word > items[largest].word)
        largest = r;

    if (largest != i) {
        swap(items[i], items[largest]);
        heapify(items, N, largest);
    }
}

void heapSort(vector<Word_item>& items) {
    size_t N = items.size();
    for (int i = N / 2 - 1; i >= 0; i--)
        heapify(items, N, i);

    for (int i = N - 1; i > 0; i--) {
        swap(items[0], items[i]);
        heapify(items, i, 0);
    }
}

//quick Sort with the first element as pivot
int partitionFirst(vector<Word_item>& items, int low, int high) {
    Word_item pivot = items[low];
    int i = low;

    for (int j = low + 1; j <= high; j++) {
        if (items[j].word < pivot.word) {
            i++;
            swap(items[i], items[j]);
        }
    }
    swap(items[i], items[low]);
    return i;
}

void quickSortFirst(vector<Word_item>& items, int low, int high) {
    if (low < high) {
        int pi = partitionFirst(items, low, high);
        quickSortFirst(items, low, pi - 1);
        quickSortFirst(items, pi + 1, high);
    }
}

//Quick Sort with a random element as pivot
int partitionRandom(vector<Word_item>& items, int low, int high) {
    srand(time(NULL));
    int random = low + rand() % (high - low);
    swap(items[random], items[high]);
    return partitionFirst(items, low, high);
}

void quickSortRandom(vector<Word_item>& items, int low, int high) {
    if (low < high) {
        int pi = partitionRandom(items, low, high);
        quickSortRandom(items, low, pi - 1);
        quickSortRandom(items, pi + 1, high);
    }
}

//Quick Sort with the median of three as pivot
int medianOfThree(vector<Word_item>& items, int a, int b, int c) {
    string maxWord = max({ items[a].word, items[b].word, items[c].word });
    string minWord = min({ items[a].word, items[b].word, items[c].word });

    string medianWord;
    if (items[a].word != maxWord && items[a].word != minWord) {
        medianWord = items[a].word;
    }
    else if (items[b].word != maxWord && items[b].word != minWord) {
        medianWord = items[b].word;
    }
    else {
        medianWord = items[c].word;
    }

    if (medianWord == items[a].word) {
        return a;
    }
    else if (medianWord == items[b].word) {
        return b;
    }
    else {
        return c;
    }
}



int partitionMedian(vector<Word_item>& items, int low, int high) {
    int medianIndex = medianOfThree(items, low, low + (high - low) / 2, high);
    //No need to swap,we can use the median element directly as the pivot
    Word_item pivot = items[medianIndex];

    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (items[j].word <= pivot.word) {
            i++;
            swap(items[i], items[j]);
        }
    }
    swap(items[i + 1], items[high]);
    return i + 1;
}

void quickSortMedian(vector<Word_item>& items, int low, int high) {
    if (low < high) {
        int pi = partitionMedian(items, low, high);
        quickSortMedian(items, low, pi - 1);
        quickSortMedian(items, pi + 1, high);
    }
}

//Merge Sort
void merge(vector<Word_item>& items, int left, int mid, int right) {
    int i = left, j = mid + 1;

    while (i <= mid && j <= right) {
        if (items[i].word <= items[j].word) {
            i++;
        }
        else {
            Word_item value = items[j];
            int index = j;

            while (index != i) {
                items[index] = items[index - 1];
                index--;
            }
            items[i] = value;

            i++;
            mid++;
            j++;
        }
    }
}

void mergeSort(vector<Word_item>& items, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(items, left, mid);
        mergeSort(items, mid + 1, right);
        merge(items, left, mid, right);
    }
}
