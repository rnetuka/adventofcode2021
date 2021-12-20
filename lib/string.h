//
// Created by rnetuka on 10.12.21.
//


#pragma once

#include <optional>
#include <string>
#include "vector.h"

namespace lib {

    class String {
    private:
        std::string data;

    public:
        const int length;

        String();
        String(const std::string& data);
        String(const char* data);
        String(int number);

        [[nodiscard]] String left_trim() const;
        [[nodiscard]] String right_trim() const;
        [[nodiscard]] String trim() const;
        [[nodiscard]] String insert(int i, const String& substring) const;
        [[nodiscard]] String lower_case() const;
        [[nodiscard]] String upper_case() const;
        [[nodiscard]] String substring(int start, int end = -1) const;
        [[nodiscard]] String replace_all(const String& substring, const String& replacement) const;

        template <typename T = String>
        vector<T> split(char delimiter = ' ') const;

        //vector<String> split(char delimiter) const;
        vector<String> split(const std::string& delimiter) const;

        bool empty() const;
        bool contains(char character) const;
        bool contains(const String& substring) const;
        bool contains_all(const String&  characters) const;
        bool starts_with(const std::string& prefix) const;
        int index_of(const String& substring) const;
        int count(char character) const;

        auto begin() const -> decltype(data.cbegin());
        auto end() const -> decltype(data.cend());

        char operator[](int i) const;
        bool operator==(const String& other) const;
        bool operator<(const String& other) const;
        bool operator>(const String& other) const;
        String& operator=(const String& other);
        String operator+(const char* other) const;
        String operator+(int number) const;
        String& operator+=(char character);
        String& operator+=(int number);
        operator int() const;
        operator std::string() const;

        friend std::ostream& operator<<(std::ostream& stream, const String& string);
        friend String sorted(const String& string);
    };

    using string = String;

    int length(const std::string& string);
    int atoi(char character);

}

namespace std {

    template <>
    struct hash<lib::String> {

        std::size_t operator()(const lib::String& string) const {
            hash<std::string> h;
            return h(string);
        }

    };

}