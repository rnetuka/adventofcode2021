//
// Created by rnetuka on 29.11.21.
//

#pragma once

#include <fstream>
#include <string>
#include <vector>

class File {
private:
    const std::string& path;

    File(const std::string& path);
public:
    static File open(const std::string& path);

    [[nodiscard]]
    std::string read() const;

    template <typename T = std::string>
    [[nodiscard]]
    std::vector<T> read_lines() const;
};