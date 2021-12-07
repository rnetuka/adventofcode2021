//
// Created by rnetuka on 06.12.21.
//

#pragma once

#include <algorithm>
#include <vector>

template <typename T, typename... Container>
std::vector<T> concatenate(const Container&... containers) {
    std::vector<T> result;
    std::vector<std::vector<T>> vectors { containers... };
    for (auto& vector : vectors)
        std::move(vector.begin(), vector.end(), std::back_inserter(result));
    return result;
}