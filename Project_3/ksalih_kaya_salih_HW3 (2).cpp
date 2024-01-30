//Salih Kaya 27890 HW3
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
#include <chrono>

using namespace std;

int timeResult1;//Stores time taken for hash table searches
int timeResult2;//Stores time taken for BST searches
int main() {
    int numberOfFiles;//Number of files to process

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
    }

    //Output unique word count and load ratio
    cout << endl << "After preprocessing, the unique word count is " << wordMap.getUniqueWordCount()
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

    bool atLeastOneDocumentContainsAllWordsHash = false;//Flag for hash table search result
    bool atLeastOneDocumentContainsAllWordsBST = false;//Flag for BST search result

    //Search using hash table
    for (const auto& fileName : fileNames) {
        stringstream resultStream;//Stream to build result string
        bool allWordsFound = true;//Flag to check if all words are found
        bool isFirstWord = true;//Flag for comma formatting

        //Checking each queried word in the document
        for (const auto& queriedWord : wordsInQuery) {
            auto startHT = chrono::high_resolution_clock::now();//Start timing for hash table search

            Word_item* result = wordMap.search(queriedWord);//Search word in hash map

            //Calculating time taken for hash table search
            auto HTTime = chrono::duration_cast<chrono::nanoseconds>
                (chrono::high_resolution_clock::now() - startHT);
            timeResult1 += HTTime.count();//Accumulate time for hash table search

            //Check if word is found in the document
            if (result) {
                bool foundInDocument = false;
                for (const auto& docItem : result->document_items) {
                    if (docItem.document_name == fileName) {
                        //Formatting output with comma if not first word
                        if (!isFirstWord) {
                            resultStream << ", ";
                        }
                        resultStream << queriedWord << " found " << docItem.count << " times";
                        foundInDocument = true;
                        isFirstWord = false;//Update flag as word is added
                        break;
                    }
                }
                if (!foundInDocument) {
                    allWordsFound = false;
                    break;
                }
            }
            else {
                allWordsFound = false;
                break;
            }
        }

        //Output result if all words are found in the document
        if (allWordsFound) {
            cout << "in Document " << fileName << ", " << resultStream.str() << "." << endl;
            atLeastOneDocumentContainsAllWordsHash = true;
        }
    }

    //Output if no document contains the queried words for hash table search
    if (!atLeastOneDocumentContainsAllWordsHash) {
        cout << "No document contains the given query" << endl;
    }

    //Search using BST
    for (const auto& fileName : fileNames) {
        stringstream resultStream;//Stream to build result string
        bool allWordsFound = true;//Flag to check if all words are found
        bool isFirstWord = true;//Flag for comma formatting

        //Checking each queried word in the document
        for (const auto& queriedWord : wordsInQuery) {
            auto startBST = chrono::high_resolution_clock::now();//Start timing for BST search

            Word_item* result = wordTree.publicSearch(queriedWord);//Search word in BST

            //Calculating time taken for BST search
            auto BSTTime = chrono::duration_cast<chrono::nanoseconds>
                (chrono::high_resolution_clock::now() - startBST);
            timeResult2 += BSTTime.count();//Accumulate time for BST search

            //Check if word is found in the document
            if (result) {
                bool foundInDocument = false;
                for (const auto& docItem : result->document_items) {
                    if (docItem.document_name == fileName) {
                        //Formatting output with comma if not first word
                        if (!isFirstWord) {
                            resultStream << ", ";
                        }
                        resultStream << queriedWord << " found " << docItem.count << " times";
                        foundInDocument = true;
                        isFirstWord = false;//Update flag as word is added
                        break;
                    }
                }
                if (!foundInDocument) {
                    allWordsFound = false;
                    break;
                }
            }
            else {
                allWordsFound = false;
                break;
            }
        }

        //Output result if all words are found in the document
        if (allWordsFound) {
            cout << "in Document " << fileName << ", " << resultStream.str() << "." << endl;
            atLeastOneDocumentContainsAllWordsBST = true;
        }
    }

    //Output if no document contains the queried words for BST search
    if (!atLeastOneDocumentContainsAllWordsBST) {
        cout << "No document contains the given query" << endl;
    }
    //Printing total times for hash table and BST searches and calculating speed-up
    cout << endl << "Time: " << timeResult1 << "\n" << endl;
    cout << "Time: " << timeResult2 << endl;

    //Calculating and outputting speed-up ratio
    double speedUp = double(timeResult2) / timeResult1;
    cout << "Speed Up: " << speedUp << endl;
    return 0;
}
