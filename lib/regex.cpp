//
// Created by rnetuka on 05.01.22.
//

#include "regex.h"

namespace lib::regex {

    Match search(const string& str, const string& pattern) {
        Match match;
        match.str = std::string(str);
        std::string p = pattern;
        std::regex_search(match.str, match.smatch, std::regex(p));
        return std::move(match);
    }

    string Match::group(int i) const {
        return smatch[i].str();
    }

    Match::operator bool() const {
        return !smatch.empty();
    }

    string Match::operator[](int i) const {
        return smatch[i].str();
    }

}