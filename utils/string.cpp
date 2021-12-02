//
// Created by rnetuka on 26.11.21.
//

#include <regex>
#include <sstream>
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