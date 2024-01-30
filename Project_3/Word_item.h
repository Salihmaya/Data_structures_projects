#pragma once
#include "Document_item.h"
#include <vector>
#include <string>
using namespace std;

struct Word_item {
    string word;
    vector<Document_item> document_items;

    Word_item() : word("") {}
    Word_item(string w) : word(w) {}

    //A method to increment the count for a specific document
    void incrementCount(const string& documentName) {
        auto it = find_if(document_items.begin(), document_items.end(),
            [&documentName](const Document_item& item) {
                return item.document_name == documentName;
            });
        if (it != document_items.end()) {
            it->count++;
        }
        else {
            //If the document does not exist in the list, add it with a count of 1
            document_items.push_back(Document_item(documentName, 1));
        }
    }

    //Add a method to get the total count of the word across all documents
    int getTotalCount() const {
        int totalCount = 0;
        for (const auto& item : document_items) {
            totalCount += item.count;
        }
        return totalCount;
    }
};
