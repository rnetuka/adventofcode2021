//
// Created by rnetuka on 10.12.21.
//

#pragma once

#include <deque>

namespace lib {

    template <typename T>
    class Stack {
    private:
        std::deque<T> elements;

    public:
        Stack() = default;

        int size() const {
            return elements.size();
        }

        bool empty() const {
            return elements.empty();
        }

        const T& top() const {
            return elements.back();
        }

        void push(const T& element) {
            elements.push_back(element);
        }

        T pop() {
            T element = elements.back();
            elements.pop_back();
            return element;
        }

        explicit operator bool() const {
            return ! empty();
        }

    };

    template <typename T>
    using stack = Stack<T>;

}