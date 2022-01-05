//
// Created by rnetuka on 13.12.21.
//

#include <fstream>
#include "file.h"

using namespace std;

namespace lib {

    File::File(const std::string& path) : path { path } {

    }

    File File::open(const std::string& path) {
        return { path };
    }

    String File::read() const {
        String result;
        fstream stream { path };
        while (stream) {
            std::string line;
            getline(stream, line);
            result += line + "\n";
        }
        return result;
    }

    template <>
    vector<String> File::read_lines() const {
        vector<String> lines;
        fstream stream { path };
        while (stream) {
            std::string line;
            getline(stream, line);
            //if (! line.empty())
            lines.push_back(line);
        }
        return lines;
    }

    template <>
    vector<int> File::read_lines() const {
        /*vector<string> lines = read_lines();
        vector<int> result(lines.size());
        transform(lines.begin(), lines.end(), result.begin(), [](auto& line) { return stoi(line); });
        return result;*/
        vector<int> lines;
        fstream stream { path };
        while (stream) {
            std::string line;
            getline(stream, line);
            if (! line.empty())
                lines.push_back(stoi(line));
        }
        return lines;
    }

}