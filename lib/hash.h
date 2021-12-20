//
// Created by rnetuka on 16.12.21.
//

#pragma once

#include <unordered_set>

namespace lib {

    template <typename T>
    void hash_combine(std::size_t& seed, const T& value) {
        std::hash<T> hasher;
        seed ^= hasher(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

}