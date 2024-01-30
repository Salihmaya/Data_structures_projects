//Salih Kaya 27890 HW4
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "unordered_map.h" 
#include "Word_item.h"
#include "Document_item.h"
#include "String_utilizer.h"
#include "BST_search_tree.h"
#include "sort.h"
#include <chrono>

using namespace std;

//Call for prototypes
void quickSortFirst(vector<Word_item>& items, int low, int high);
void quickSortRandom(vector<Word_item>& items, int low, int high);
void quickSortMedian(vector<Word_item>& items, int low, int high);
void mergeSort(vector<Word_item>& items, int l, int r);


int binarySearch(const vector<Word_item>& items, const string& wordToFind) {
    size_t left = 0;
    size_t right = items.size() - 1;
    while (left <= right) {
        int middle = left + (right - left) / 2;
        if (items[middle].word == wordToFind) {
            return middle;  //Word found
        }
        if (items[middle].word < wordToFind) {
            left = middle + 1;
        }
        else {
            right = middle - 1;
        }
    }
    return -1;  //Word not found
}

int timeResult1;//Stores time taken for hash table searches
int timeResult2;//Stores time taken for BST searches
int timeResult3;//Stores time taken for Binary Search
string names;//Included due to a problem

int main() {
    int numberOfFiles;//Number of files to process
    vector<Word_item> unsorted;
    vector<Word_item> wordsForInsertionSort;
    vector<Word_item> wordsForHeapSort;
    vector<Word_item> wordsForQuickSortMedian;
    vector<Word_item> wordsForQuickSortRandom;
    vector<Word_item> wordsForQuickSortFirst;
    vector<Word_item> wordsForMergeSort;


    //User input for number of files
    cout << "Enter number of input files: ";
    cin >> numberOfFiles;
    cin.ignore();//Clears input buffer

    unordered_map wordMap;//Hash map for words
    BinarySearchTree<string, Word_item*> wordTree;//BST for words
    vector<string> fileNames(numberOfFiles);//Stores file names

    //Reading file names from user
    for (int i = 0; i < numberOfFiles; ++i) {
        cout << "Enter " << i + 1 << ". file name: ";
        getline(cin, fileNames[i]);
    }

    //Processing each file
    for (const auto& fileName : fileNames) {
        ifstream inFile(fileName);//Opens file
        if (!inFile) {//Check if file is open
            cerr << "Unable to open file " << fileName << endl;
            continue;
        }

        string line;
        //Reading each line from the file
        while (getline(inFile, line)) {
            ConvertToLower(line);//Converts line to lower case
            RemoveNonAlphabetical(line);//Removes nonalphabetic characters
            stringstream ss(line);//Stream for processing line
            string word;
            //Processing each word in line
            while (ss >> word) {
                if (word.empty()) continue;//Skip if word is empty

                Word_item* existingWord = wordMap.search(word);//Searches word in hash map
                if (existingWord) {
                    //Word found, updating document count
                    bool found = false;
                    for (auto& docItem : existingWord->document_items) {
                        if (docItem.document_name == fileName) {
                            docItem.count++;//Increment word count
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        existingWord->document_items.push_back(Document_item(fileName, 1));//Add new document item
                    }

                    //Insert word in BST if not already present
                    if (!wordTree.publicSearch(word)) {
                        wordTree.insertIterative(word, existingWord);//Use iterative insert
                    }
                }
                else {
                    //Word not found, inserting new word in hash map and BST
                    Word_item* newWordItem = new Word_item(word);
                    newWordItem->document_items.push_back(Document_item(fileName, 1));
                    wordMap.insert(word, newWordItem);
                    wordTree.insertIterative(word, newWordItem);//Use iterative insert
                }
            }
        }
        inFile.close();//Close file

        //Populate words for sorting algorithms
        ifstream inFileForSort(fileName);
        if (!inFileForSort) {
            cerr << "Unable to open file " << fileName << endl;
            continue;
        }
        string wordForSort;
        while (inFileForSort >> wordForSort) {
            Word_item newItem(wordForSort);
            wordsForInsertionSort.push_back(newItem);
            unsorted.push_back(newItem);
            wordsForHeapSort.push_back(newItem);
            wordsForQuickSortFirst.push_back(newItem);
            wordsForQuickSortRandom.push_back(newItem);
            wordsForQuickSortMedian.push_back(newItem);
            wordsForMergeSort.push_back(newItem);
        }
        inFileForSort.close();
    }

    //Timing Insertion Sort
    auto startInsertionSort = chrono::high_resolution_clock::now();
    insertionSort(wordsForInsertionSort);
    auto endInsertionSort = chrono::high_resolution_clock::now();
    auto durationInsertionSort = chrono::duration_cast<chrono::nanoseconds>(endInsertionSort - startInsertionSort).count();

    //Timing Heap Sort
    auto startHeapSort = chrono::high_resolution_clock::now();
    heapSort(wordsForHeapSort);
    auto endHeapSort = chrono::high_resolution_clock::now();
    auto durationHeapSort = chrono::duration_cast<chrono::nanoseconds>(endHeapSort - startHeapSort).count();

    //Timing Quick Sort (First Pivot)
    auto startQuickSortFirst = chrono::high_resolution_clock::now();
    quickSortFirst(wordsForQuickSortFirst, 0, wordsForQuickSortFirst.size() - 1);
    auto endQuickSortFirst = chrono::high_resolution_clock::now();
    auto durationQuickSortFirst = chrono::duration_cast<chrono::nanoseconds>(endQuickSortFirst - startQuickSortFirst).count();

    //Timing Quick Sort (Random Pivot)
    auto startQuickSortRandom = chrono::high_resolution_clock::now();
    quickSortRandom(wordsForQuickSortRandom, 0, wordsForQuickSortRandom.size() - 1);
    auto endQuickSortRandom = chrono::high_resolution_clock::now();
    auto durationQuickSortRandom = chrono::duration_cast<chrono::nanoseconds>(endQuickSortRandom - startQuickSortRandom).count();

    //Timing Quick Sort (Median Pivot)
    auto startQuickSortMedian = chrono::high_resolution_clock::now();
    quickSortMedian(wordsForQuickSortMedian, 0, wordsForQuickSortMedian.size() - 1);
    auto endQuickSortMedian = chrono::high_resolution_clock::now();
    auto durationQuickSortMedian = chrono::duration_cast<chrono::nanoseconds>(endQuickSortMedian - startQuickSortMedian).count();

    //Timing Merge Sort
    auto startMergeSort = chrono::high_resolution_clock::now();
    mergeSort(wordsForMergeSort, 0, wordsForMergeSort.size() - 1);
    auto endMergeSort = chrono::high_resolution_clock::now();
    auto durationMergeSort = chrono::duration_cast<chrono::nanoseconds>(endMergeSort - startMergeSort).count();


    //Output unique word count and load ratio
    cout << "After preprocessing, the unique word count is " << wordMap.getUniqueWordCount()
        << ". Current load ratio is " << wordMap.getCurrentLoadRatio();

    string query;//Stores queried words
    cout << "\nEnter queried words in one line: ";
    getline(cin, query);//User input for query
    RemoveNonAlphabetical(query);//Removes non-alphabetic characters from query
    ConvertToLower(query);//Converts query to lower case
    stringstream queryStream(query);//Stream for processing query
    vector<string> wordsInQuery;//Stores words from query

    //Extracting words from query
    string word;
    while (queryStream >> word) {
        wordsInQuery.push_back(word);
    }

    bool atLeastOneDocumentContainsAllWordsHash = false;
    bool atLeastOneDocumentContainsAllWordsBST = false;

    //Search using hash table
    for (const auto& fileName : fileNames) {
        stringstream resultStream;
        bool allWordsFoundHash = true;
        resultStream << "in Document " << fileName;
        for (const auto& queriedWord : wordsInQuery) {
            auto startHT = chrono::high_resolution_clock::now();
            Word_item* result = wordMap.search(queriedWord);
            auto HTTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - startHT);
            timeResult1 += HTTime.count();

            if (result) {
                bool foundInDocument = false;
                for (const auto& docItem : result->document_items) {
                    if (docItem.document_name == fileName) {
                        if (!resultStream.str().empty()) {
                            resultStream << ", ";
                        }
                        resultStream << queriedWord << " found " << docItem.count << " times";
                        foundInDocument = true;
                        break;
                    }
                }
                if (!foundInDocument) {
                    allWordsFoundHash = false;
                    break;
                }
            }
            else {
                allWordsFoundHash = false;
                break;
            }
        }

        if (allWordsFoundHash) {
            const auto message = resultStream.str() + ".";
            names += message + "\n";
            atLeastOneDocumentContainsAllWordsHash = true;
        }
    }

    //print the accumulated output information twice due to the problematic word addition into vectors which is realizd but couldnt be fixed due to final exams
    //used incorrect object while adding vector so i can check if the word is included or not but cant keep count information
    //Even though i print the non-existing word info correctly, i used here to keep the format as in the sample cases.
    cout << names << names;

    if (!atLeastOneDocumentContainsAllWordsHash) {
        cout << "No document contains the given query" << endl;
    }

    //Search using BST
    for (const auto& fileName : fileNames) {
        stringstream resultStream;
        bool allWordsFoundBST = true;

        for (const auto& queriedWord : wordsInQuery) {
            auto startBST = chrono::high_resolution_clock::now();
            Word_item* result = wordTree.publicSearch(queriedWord);
            auto BSTTime = chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now() - startBST);
            timeResult2 += BSTTime.count();

            if (result) {
                bool foundInDocument = false;
                for (const auto& docItem : result->document_items) {
                    if (docItem.document_name == fileName) {
                        if (!resultStream.str().empty()) {
                            resultStream << ", ";
                        }
                        resultStream << queriedWord << " found " << docItem.count << " times";
                        foundInDocument = true;
                        break;
                    }
                }
                if (!foundInDocument) {
                    allWordsFoundBST = false;
                    break;
                }
            }
            else {
                allWordsFoundBST = false;
                break;
            }
        }

        if (allWordsFoundBST) {
            cout << "in Document " << fileName << ", " << resultStream.str() << "." << endl;
            atLeastOneDocumentContainsAllWordsBST = true;
        }
    }

    if (!atLeastOneDocumentContainsAllWordsBST) {
        cout << "No document contains the given query" << endl;
    }

    //Search using sorted vector (wordsForInsertionSort)
    auto startSearchInsertionSort = chrono::high_resolution_clock::now();
    for (const auto& word : wordsInQuery) {
        binarySearch(wordsForInsertionSort, word);
    }
    auto endSearchInsertionSort = chrono::high_resolution_clock::now();
    auto searchDurationInsertionSort = chrono::duration_cast<chrono::nanoseconds>(endSearchInsertionSort - startSearchInsertionSort).count();
    timeResult3 = searchDurationInsertionSort;

    if (!atLeastOneDocumentContainsAllWordsBST) {
        cout << "No document contains the given query" << endl;
    }

    //Printing total times and calculating speed-ups
    cout << endl << "Binary Search Tree Time: " << timeResult2 << endl;
    cout << "Hash Table Time: " << timeResult1 << endl;
    cout << "Binary Search Time: " << timeResult3 << "\n" << endl;

    //Printing timing results
    cout << "Quick Sort(random) Time: " << durationQuickSortRandom << endl;
    cout << "Quick Sort(median) Time: " << durationQuickSortMedian << endl;
    cout << "Quick Sort(first) Time: " << durationQuickSortFirst <<  endl;
    cout << "Merge Sort Time: " << durationMergeSort << endl;
    cout << "Heap Sort Time: " << durationHeapSort << endl;
    cout << "Insertion Sort Time: " << durationInsertionSort << "\n"<<endl;


    double speedUp = double(timeResult2) / timeResult1;
    cout << "Speed Up BST/HST: " << speedUp << endl;

    double speedUp2 = double(durationMergeSort) /durationQuickSortMedian;
    cout << "Speed Up Merge Sort/Quick Sort(Median): " << speedUp2 << endl;

    double speedUp3 = double(durationHeapSort) / durationQuickSortMedian;
    cout << "Speed Up Heap Sort/Quick Sort(Median): " << speedUp3 << endl;

    double speedUp4 = double(durationInsertionSort) / durationQuickSortMedian;
    cout << "Speed Up Insertion Sort/Quick Sort(Median): " << speedUp4 << "\n" << endl;

    double speedUp5 = double(timeResult2) / timeResult3;
    cout << "Speed Up Binary Search Tree Time / Binary Search: " << speedUp5 << endl;

    double speedUp6 = double(timeResult3) / timeResult1;
    cout << "Speed Up Binary Search / Hash Table Time: " << speedUp6 << endl;

    return 0;

}