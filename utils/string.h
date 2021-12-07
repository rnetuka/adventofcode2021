//
// Created by rnetuka on 26.11.21.
//

#pragma once

#include <string>
#include <vector>

char to_char(int digit);
int stoi(const std::string& string, int base);
std::string left_trim(const std::string& string);
std::string right_trim(const std::string& string);
std::string trim(const std::string& string);

template <typename T = std::string>
std::vector<T> split(const std::string& str, char delimiter = ' ');

std::vector<std::string> split(const std::string& str, const std::string& delimiter);