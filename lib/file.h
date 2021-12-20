//
// Created by rnetuka on 13.12.21.
//

#pragma once

#include "string.h"
#include "vector.h"

namespace lib {

    class File {
    private:
        const std::string& path;

        File(const std::string& path);

    public:
        static File open(const std::string& path);

        [[nodiscard]]
        String read() const;

        template <typename T = String>
        [[nodiscard]]
        vector<T> read_lines() const;
    };

}