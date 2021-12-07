//
// Created by rnetuka on 26.11.21.
//

#include <regex>
#include <sstream>
#include <stdexcept>
#include "string.h"

using namespace std;

template <>
vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream stream { str };
    while (getline(stream, token, delimiter))
        tokens.push_back(token);
    return tokens;
}

template <>
vector<int> split(const string& str, char delimiter) {
    vector<int> tokens;
    string token;
    istringstream stream { str };
    while (getline(stream, token, delimiter))
        tokens.push_back(stoi(token));
    return tokens;
}

char to_char(int digit) {
    if (digit < 0 || digit > 9)
        throw invalid_argument("Digit out of range");
    return static_cast<char>(digit + '0');
}

int stoi(const string& string, int base) {
    return std::stoi(string, nullptr, base);
}

string left_trim(const string& str) {
    string result = str;
    result.erase(result.begin(), find_if(result.begin(), result.end(), [](char c) {
        return !isspace(c);
    }));
    return result;
}

string right_trim(const string& str) {
    string result = str;
    result.erase(find_if(result.rbegin(), result.rend(), [](char c) {
        return !isspace(c);
    }).base(), result.end());
    return result;
}

string trim(const string& str) {
    string result = left_trim(str);
    return right_trim(result);
}