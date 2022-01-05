//
// Created by rnetuka on 05.01.22.
//

#pragma once

#include <regex>
#include "string.h"

namespace lib::regex {

    class Match {
    private:
        std::string str;
        std::smatch smatch;

    public:
        string group(int i) const;

        operator bool() const;
        string operator[](int i) const;

        friend Match search(const string& str, const string& pattern);
    };

    Match search(const string& str, const string& pattern);

}