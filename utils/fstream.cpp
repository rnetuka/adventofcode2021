//
// Created by rnetuka on 29.11.21.
//

#include <algorithm>
#include "fstream.h"

using namespace std;

File::File(const string& path) : path { path } {

}

File File::open(const string& path) {
    return { path };
}

string File::read() const {
    fstream stream { path };
    string result;
    stream >> result;
    return result;
}

template <>
vector<string> File::read_lines() const {
    vector<string> lines;
    fstream stream { path };
    while (stream) {
        string line;
        getline(stream, line);
        if (! line.empty())
            lines.push_back(line);
    }
    return lines;
}

template <>
vector<int> File::read_lines() const {
    vector<string> lines = read_lines();
    vector<int> result(lines.size());
    transform(lines.begin(), lines.end(), result.begin(), [](auto& line) { return stoi(line); });
    return result;
}