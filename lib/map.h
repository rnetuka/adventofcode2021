//
// Created by rnetuka on 15.12.21.
//

#pragma once

#include <algorithm>
#include <map>

namespace lib {

    template <typename Key, typename Value>
    using map = std::map<Key, Value>;

    template <typename Key, typename Value>
    struct Entry {
        Key key;
        Value value;
    };

    template <typename Key, typename Value>
    Entry<Key, Value> min_element(const map<Key, Value>& map) {
        auto pair = *std::min_element(map.begin(), map.end(), [](auto& a, auto& b) { return a.second < b.second; });
        return { pair.first, pair.second };
    }

    template <typename Key, typename Value>
    Value min_value(const map<Key, Value>& map) {
        return min_element(map).value;
    }

    template <typename Key, typename Value>
    Entry<Key, Value> max_element(const map<Key, Value>& map) {
        auto pair = *std::max_element(map.begin(), map.end(), [](auto& a, auto& b) { return a.second < b.second; });
        return { pair.first, pair.second };
    }

    template <typename Key, typename Value>
    Value max_value(const map<Key, Value>& map) {
        return max_element(map).value;
    }

}