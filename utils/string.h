//
// Created by rnetuka on 26.11.21.
//

#pragma once

#include <array>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& str, char delimiter = ' ');
char to_char(int digit);
int stoi(const std::string& str, int base);