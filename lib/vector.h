//
// Created by rnetuka on 10.12.21.
//

#pragma once

#include <algorithm>
#include <stdexcept>
#include <deque>
#include <functional>

namespace lib {

    template <typename T>
    class Vector {
    private:
        std::deque<T> elements;

    public:

        Vector() = default;

        Vector(std::initializer_list<T>&& elements) : elements { elements } {

        }

        int size() const {
            return elements.size();
        }

        bool empty() const {
            return elements.empty();
        }

        bool contains(const T& element) const {
            return std::find(elements.begin(), elements.end()) != elements.end();
        }

        void push_front(const T& element) {
            elements.push_front(element);
        }

        void push_back(const T& element) {
            elements.push_back(element);
        }

        T pop_front() {
            T element = elements.front();
            elements.pop_front();
            return element;
        }

        void pop_back() {
            elements.pop_back();
        }

        void resize(int size) {
            elements.resize(size);
        }

        void erase(int i) {
            elements.erase(elements.begin() + i);
        }

        void erase_if(std::function<bool(const T&)> predicate) {
            std::erase_if(elements, predicate);
        }

        template <typename UnaryFunction>
        bool any_of(UnaryFunction check) const {
            return std::any_of(elements.begin(), elements.end(), check);
        }

        template <typename UnaryFunction>
        bool all_of(UnaryFunction check) const {
            return std::all_of(elements.begin(), elements.end(), check);
        }

        T& operator[](int i) {
            if (i < 0 || i > size())
                throw std::out_of_range("Index is out of range");
            return elements[i];
        }

        const T& operator[](int i) const {
            if (i < 0 || i > size())
                throw std::out_of_range("Index is out of range");
            return elements[i];
        }

        Vector& operator+=(const Vector& other) {
            std::move(other.begin(), other.end(), std::back_inserter(elements));
            return *this;
        }

        auto begin() -> decltype(elements.begin()) {
            return elements.begin();
        }

        auto end() -> decltype(elements.end()) {
            return elements.end();
        }

        auto begin() const -> decltype(elements.begin()) {
            return elements.begin();
        }

        auto end() const -> decltype(elements.end()) {
            return elements.end();
        }

        template <typename UnaryFunction>
        friend bool any_of(const Vector vector, UnaryFunction check) {
            return std::any_of(vector.elements.begin(), vector.elements.end(), check);
        }

        template <typename UnaryFunction>
        friend bool all_of(const Vector vector, UnaryFunction check) {
            return std::all_of(vector.elements.begin(), vector.elements.end(), check);
        }

    };

    template <typename T>
    using vector = Vector<T>;

}