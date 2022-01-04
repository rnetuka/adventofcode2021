//
// Created by rnetuka on 04.01.22.
//

#include <bitset>
#include <sstream>
#include "number.h"

namespace lib {

    Integer::Integer() {
        value = 0;
    }

    Integer::Integer(int value) {
        this->value = value;
    }

    Integer::Integer(const string& string) : value { 0 } {
        if (string.starts_with("0x")) {
            std::stringstream stream;
            stream << std::hex << string;
            stream >> value;
        } else if (string.starts_with("0b")) {
            value = stoi(string, 2);
        } else {
            value = stoi(string);
        }
    }

    Integer Integer::from_hex(char hex) {
        string str;
        str += hex;
        return Integer::from_hex(str);
    }

    Integer Integer::from_hex(const string& hex) {
        return hex.starts_with("0x") ? Integer(hex) : Integer(hex.prepend("0x"));
    }

    Integer Integer::from_bin(const string& bin) {
        return { stoi(bin, 2) };
    }

    string Integer::hex() const {
        std::stringstream stream;
        stream << std::hex << value;
        return stream.str();
    }

    string Integer::bin() const {
        if (value == 0)
            return "0";

        string s = std::bitset<64>(value).to_string();
        int i = s.index_of("1");
        return s.substring(i);
    }

    Integer::operator int() const {
        return value;
    }

}