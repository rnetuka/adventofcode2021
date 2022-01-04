//
// Created by rnetuka on 10.12.21.
//

#include <algorithm>
#include <regex>
#include <sstream>
#include "string.h"

namespace lib {

    String::String() : length { 0 } {

    }

    String::String(const std::string& data) : data { data }, length { static_cast<int>(data.length()) } {

    }

    String::String(const char* data) : String { std::string { data }} {

    }

    String::String(int number) : String { std::to_string(number) } {

    }

    String::String(char character) : length { 1 } {
        data += character;
    }

    String String::left_trim() const {
        std::string result = data;
        result.erase(result.begin(), find_if(result.begin(), result.end(), [](char c) {
            return !isspace(c);
        }));
        return result;
    }

    String String::right_trim() const {
        std::string result = data;
        result.erase(find_if(result.rbegin(), result.rend(), [](char c) {
            return !isspace(c);
        }).base(), result.end());
        return result;
    }

    String String::trim() const {
        String result = left_trim();
        return result.right_trim();
    }

    String String::lower_case() const {
        std::string result = data;
        std::transform(result.begin(), result.end(), result.begin(), [](char c){ return std::tolower(c); });
        return { result };
    }

    String String::upper_case() const {
        std::string result = data;
        std::transform(result.begin(), result.end(), result.begin(), [](char c){ return std::toupper(c); });
        return { result };
    }

    String String::substring(int start, int end) const {
        int n;
        if (end == -1)
            n = length - start;
        else
            n = end - start;
        return { data.substr(start, n) };
    }

    String String::replace_all(const String& substring, const String& replacement) const {
        std::string result = std::regex_replace(data, std::regex(std::string(substring)), std::string(replacement));
        return { result };
    }

    String String::prepend(char c, int times) const {
        std::string result;
        for (int i = 0; i < times; i++)
            result += c;
        result += data;
        return { result };
    }

    String String::prepend(const String& str) const {
        return { str.data + data };
    }

    String String::insert(int i, const String& substring) const {
        std::string copy = data;
        copy.insert(i + 1, substring.data);
        return { copy };
    }

    bool String::empty() const {
        return data.empty();
    }

    bool String::contains(char character) const {
        return data.find(character) != std::string::npos;
    }

    bool String::contains(const String& substring) const {
        return data.find(substring.data) != std::string::npos;
    }

    bool String::contains_all(const String& characters) const {
        for (char c : characters)
            if (! contains(c))
                return false;
        return true;
    }

    bool String::starts_with(const std::string& prefix) const {
        return data.starts_with(prefix);
    }

    int String::index_of(const String& substring) const {
        return data.find(substring.data);
    }

    int String::count(char character) const {
        int count = 0;
        for (char c : data)
            if (c == character)
                count++;
        return count;
    }

    auto String::begin() const -> decltype(data.cbegin()) {
        return data.cbegin();
    }

    auto String::end() const -> decltype(data.cend()) {
        return data.cend();
    }

    char String::operator[](int i) const {
        return data[i];
    }

    bool String::operator==(const String& other) const {
        return data == other.data;
    }

    bool String::operator<(const String& other) const {
        return data < other.data;
    }

    bool String::operator>(const String& other) const {
        return data > other.data;
    }

    String& String::operator=(const String& other) {
        const_cast<int&>(length) = other.length;
        data = other.data;
        return *this;
    }

    String String::operator+(const char* other) const {
        return data + other;
    }

    String String::operator+(int number) const {
        return data + std::to_string(number);
    }

    String& String::operator+=(char character) {
        data += character;
        return *this;
    }

    String& String::operator+=(int number) {
        data += itoa(number);
        return *this;
    }

    String& String::operator+=(const char* str) {
        data += str;
        return *this;
    }

    String& String::operator+=(const String& other) {
        data += other.data;
        return *this;
    }

    String::operator int() const {
        return stoi(data);
    }

    String::operator std::string() const {
        return data;
    }

    template <>
    vector<String> String::split(char delimiter) const {
        vector<String> tokens;
        std::string token;
        std::istringstream stream { data };
        while (getline(stream, token, delimiter))
            tokens.push_back(token);
        return tokens;
    }

    template <>
    vector<int> String::split(char delimiter) const {
        vector<int> tokens;
        std::string token;
        std::istringstream stream { data };
        while (getline(stream, token, delimiter))
            tokens.push_back(stoi(token));
        return tokens;
    }

    std::string escaped(const std::string& input) {
        std::string output;
        output.reserve(input.size());
        for (char c: input)
            switch (c) {
                case '|': output += "\\|"; break;
                default:  output += c;
            }
        return output;
    }

    vector<String> String::split(const std::string& delimiter) const {
        std::regex re { escaped(delimiter) };
        std::sregex_token_iterator it { data.begin(), data.end(), re, -1 };
        std::vector<string> tokens { it, {} };
        tokens.erase(
                std::remove_if(tokens.begin(), tokens.end(), [](const std::string& s) { return s.size() == 0; }),
                tokens.end());

        vector<String> result;
        for (string& token : tokens)
            result.push_back(token);
        return result;
    }

    vector<char> String::chars() const {
        vector<char> result;
        for(char c : data)
            result.push_back(c);
        return result;
    }

    std::ostream& operator<<(std::ostream& stream, const String& string) {
        return stream << string.data;
    }

    int length(const std::string& string) {
        return string.length();
    }

    int atoi(char character) {
        return character - '0';
    }

    char itoa(int digit) {
        if (digit < 0 || digit > 9)
            throw std::invalid_argument("Digit out of range");
        return static_cast<char>(digit + '0');
    }

    int stoi(const String& string, int base) {
        return std::stoi(string, nullptr, base);
    }

    long stol(const String& string, int base) {
        return std::stol(string, nullptr, base);
    }

    String sorted(const String& str) {
        std::string result = str.data;
        std::sort(result.begin(), result.end());
        return { result };
    }

}