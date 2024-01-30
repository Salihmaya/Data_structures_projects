#pragma once
#include "Document_item.h"
#include <vector>
using namespace std;

struct Word_item {
	string word;
	vector <Document_item> document_items;
	Word_item(): word(""){}
	Word_item(string w) : word(w){}
};