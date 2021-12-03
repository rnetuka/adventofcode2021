//
// Created by rnetuka on 26.11.21.
//

#include <regex>
#include <sstream>
#include <stdexcept>
#include "string.h"

using namespace std;

vector<string> split(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream stream { str };
    while (getline(stream, token, delimiter))
        tokens.push_back(token);
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