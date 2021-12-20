//
// Created by rnetuka on 10.12.21.
//

#pragma once

#include <initializer_list>
#include <unordered_set>

namespace lib {

    template <typename T>
    class Set {
    private:
        std::unordered_set<T> elements;

    public:
        Set() {

        }

        Set(std::initializer_list<T>&& elements) {
            for (auto& element : elements)
                this->elements.insert(element);
        }

        template <typename Container>
        Set(const Container& container) : elements { container.begin(), container.end() } {

        }

        int size() const {
            return elements.size();
        }

        bool empty() const {
            return elements.empty();
        }

        bool contains(const T& element) {
            return elements.contains(element);
        }

        void insert(const T& element) {
            elements.insert(element);
        }

        void erase(const T& element) {
            elements.erase(element);
        }

        template <typename UnaryFunction>
        void erase_if(UnaryFunction predicate) {
            std::erase_if(elements, predicate);
        }

        auto begin() -> decltype(elements.begin()) {
            return elements.begin();
        }

        auto end() -> decltype(elements.end()) {
            return elements.end();
        }

        auto begin() const -> decltype(elements.cbegin()) {
            return elements.cbegin();
        }

        auto end() const -> decltype(elements.cend()) {
            return elements.cend();
        }

    };

    template <typename T>
    using set = Set<T>;

}