#include "string_utilizer.h"
#include <regex>
#include <cctype>
#include <cstdlib>
#include <cassert>
#include <sstream>

using namespace std;

// Converts all characters in the string to lowercase.
void ConvertToLower(string& str) {
    int length = str.length();
    for (int i = 0; i < length; i++) {
        str[i] = tolower(str[i]);
    }
}

// Converts all characters in the string to uppercase.
void ConvertToUpper(string& str) {
    int length = str.length();
    for (int i = 0; i < length; i++) {
        str[i] = toupper(str[i]);
    }
}

// Removes punctuation from the beginning and end of the string by using regular expressions
void RemovePunctuation(string& word) {
    // Regular expression to match any punctuation
    regex punctuationRegex(R"([^\w\s])");

    // Replace punctuation with empty string
    word = regex_replace(word, punctuationRegex, "");
}



// Removes whitespace from the beginning and end of the string.
void RemoveWhitespace(string& word) {
    int first = 0, last = word.length() - 1;

    while (first < word.length() && isspace(word[first])) {
        first++;
    }

    while (last >= 0 && isspace(word[last])) {
        last--;
    }

    word = word.substr(first, last - first + 1);
}

// Returns a lowercase version of the given string.
string GetLowercaseString(const string& str) {
    string word = str;
    ConvertToLower(word);
    return word;
}

// Returns an uppercase version of the given string.
string GetUppercaseString(const string& str) {
    string word = str;
    ConvertToUpper(word);
    return word;
}

// Converts an integer to a string.
string IntToString(int number) {
    ostringstream output;
    output << number;
    return output.str();
}

// Alternative function to convert an integer to a string.
string ConvertIntToString(int number) {
    return IntToString(number);
}

// Converts a double to a string.
string DoubleToString(double number) {
    ostringstream output;
    output << number;
    return output.str();
}

// Converts a string to an integer. Returns 0 if conversion is not possible.
int StringToInt(const string& str) {
    return atoi(str.c_str());
}

// Converts a string to a double. Returns 0.0 if conversion is not possible.
double StringToDouble(const string& str) {
    return atof(str.c_str());
}
