#pragma once
#include <string>
using namespace std;

struct Document_item {
	string document_name;
	int count;

	Document_item() : document_name(""), count(0) {}
	Document_item(string name, int count) : document_name(name), count(count){}

};