#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "AVL_Search_Tree.h"
#include "Word_item.h"
#include "Document_item.h"
#include "String_utilizer.h"

using namespace std;

int main() {
    int numberOfFiles;
    cout << "Enter number of input files: ";
    cin >> numberOfFiles;
    cin.ignore(); // To consume the newline character after the number input

    vector<AVLSearchTree<string, Word_item*>> trees(numberOfFiles);
    vector<string> fileNames(numberOfFiles);

    // Read file names and preprocess documents
    for (int i = 0; i < numberOfFiles; ++i) {
        cout << "Enter " << i + 1 << ". file name: ";
        getline(cin, fileNames[i]);
        ifstream inFile(fileNames[i]);

        if (!inFile) {
            cerr << "Unable to open file " << fileNames[i] << endl;
            return 1; // Exit with error code
        }

        string line;
        while (getline(inFile, line)) {
            ConvertToLower(line);
            stringstream ss(line);
            string word;
            while (ss >> word) {
                RemovePunctuation(word);
                if (word.empty()) continue; // Skip empty words resulting from punctuation removal

                Word_item* existingWord = trees[i].publicSearch(word);
                if (existingWord) {
                    existingWord->document_items[0].count++;
                }
                else {
                    Word_item* newWordItem = new Word_item(word);
                    newWordItem->document_items.push_back(Document_item(fileNames[i], 1));
                    trees[i].insert(word, newWordItem);
                }
            }
        }
        inFile.close();
    }

    // Query processing
string query;
cout << "\nEnter queried words in one line: ";
while (getline(cin, query)) {
    if (query == "ENDOFINPUT") {
        break; // Exit the loop if the command is ENDOFINPUT
    }

    if (query.rfind("REMOVE", 0) == 0) { // Check if the command starts with REMOVE
        string wordToRemove = query.substr(7); // Extract the word to remove
        ConvertToLower(wordToRemove);
        RemovePunctuation(wordToRemove);

        bool removed = false;
        for (int i = 0; i < numberOfFiles; ++i) {
            if (trees[i].publicSearch(wordToRemove)) {
                trees[i].remove(wordToRemove); // Remove the word from the tree
                removed = true;
            }
        }

        if (removed) {
            cout << wordToRemove << " has been REMOVED" << endl;
        }
        else {
            cout << "No document contains the word " << wordToRemove << endl;
        }
    }
    else {
        stringstream queryStream(query);
        vector<string> wordsInQuery;
        string word;
        while (queryStream >> word) {
            RemovePunctuation(word);
            ConvertToLower(word);
            if (!word.empty()) {
                wordsInQuery.push_back(word);
            }
        }

        bool noDocumentContainsQuery = true;
        for (int i = 0; i < numberOfFiles; ++i) {
            stringstream resultStream;
            bool allWordsFound = true;
            for (const auto& word : wordsInQuery) {
                Word_item* result = trees[i].publicSearch(word);
                if (result) {
                    resultStream << word << " found " << result->document_items[0].count << " times, ";
                } else {
                    allWordsFound = false;
                    break;
                }
            }

            if (allWordsFound) {
                noDocumentContainsQuery = false;
                string results = resultStream.str();
                // Remove the last comma and space
                if (!results.empty()) results.erase(results.length() - 2);
                cout << "in Document " << fileNames[i] << ", " << results << "." << endl;
            }
        }

        if (noDocumentContainsQuery) {
            cout << "No document contains the given query" << endl;
        }
    }

    cout << "\nEnter queried words in one line: ";
}

//cout << "Program ended." << endl;
return 0;
}
