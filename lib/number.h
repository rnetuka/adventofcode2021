//
// Created by rnetuka on 04.01.22.
//

#pragma once

#include "string.h"

namespace lib {

    class Integer {
    private:
        int value;

    public:
        Integer();
        Integer(int value);
        Integer(const string& string);
        static Integer from_hex(char hex);
        static Integer from_hex(const string& string);
        static Integer from_bin(const string& string);

        string hex() const;
        string bin() const;

        operator int() const;
    };

    using integer = Integer;

}