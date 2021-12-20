//
// Created by rnetuka on 10.12.21.
//

#pragma once

#include <initializer_list>
#include <deque>

namespace lib {

    template <typename T>
    class Queue {
    private:
        std::deque<T> elements;

    public:
        Queue() = default;

        Queue(std::initializer_list<T>&& init_list) : elements { init_list } {

        }

        int size() const {
            return elements.size();
        }

        bool empty() const {
            return elements.empty();
        }

        void push(const T& element) {
            elements.push_front(element);
        }

        T pop() {
            T result = elements.front();
            elements.pop_front();
            return result;
        }

    };

    template <typename T>
    using queue = Queue<T>;

}