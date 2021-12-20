//
// Created by rnetuka on 16.12.21.
//

#pragma once

#include <algorithm>
#include <optional>
#include "set.h"
#include "vector.h"

namespace lib {

    template <typename T>
    T min_element(const vector<T>& values) {
        return *std::min_element(values.begin(), values.end());
    }

    template <typename T, typename Comparison>
    std::optional<T> min_element(const set<T>& values, Comparison comparison) {
        auto it = std::min_element(values.begin(), values.end(), comparison);
        return it == values.end() ? std::nullopt : std::make_optional(*it);
    }

    template <typename T>
    T max_element(const vector<T>& values) {
        return *std::max_element(values.begin(), values.end());
    }

    /*template <typename T>
    vector<T> sorted(const vector<T>& values) {
        vector<T> result = values;
        std::sort(result.begin(), result.end());
        return result;
    }*/

    template <typename Container>
    Container sorted(const Container& container) {
        Container result = container;
        std::sort(result.begin(), result.end());
        return result;
    }

    template <typename T>
    vector<T> reversed(const vector<T>& values) {
        vector<T> result = values;
        std::reverse(result.begin(), result.end());
        return result;
    }

    template <typename T2, typename T1, typename UnaryOperation>
    Vector<T2> transform(const Vector<T1>& container, UnaryOperation operation) {
        Vector<T2> result;
        result.resize(container.size());
        std::transform(container.begin(), container.end(), result.begin(), operation);
        return result;
    }

}