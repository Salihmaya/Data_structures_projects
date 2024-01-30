#pragma once
#include <iostream>
#include <string>

using namespace std;
//ALL THE FUNCTION IMPLEMENTATIONS ARE WRITTEN BEFOREHAND IN CASE THEY ARE NEEDED


// Converts all alphabetic characters in a string to lowercase.
// Only affects uppercase letters.
void ConvertToLower(string& str);

// Converts all alphabetic characters in a string to uppercase.
// Only affects lowercase letters.
void ConvertToUpper(string& str);

// Removes leading and trailing white space from a string.
void RemoveWhitespace(string& str);

// Returns a new string which is the lowercase equivalent of the input string.
string GetLowercaseString(const string& str);

// Returns a new string which is the uppercase equivalent of the input string.
string GetUppercaseString(const string& str);

// Converts a string to its integer equivalent.
int StringToInt(const string& str);

// Converts a string to its double equivalent.
double StringToDouble(const string& str);

// Converts an integer to its string equivalent.
string IntToString(int number);

// Similar to IntToString, converts an integer to a string.
string ConvertIntToString(int number);

// Converts a double to its string equivalent.
string DoubleToString(double number);
//Removing nonalphabetical chars
void RemoveNonAlphabetical(string& text);