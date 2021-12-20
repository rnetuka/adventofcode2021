//
// Created by rnetuka on 02.12.21.
//

#pragma once

#include <iostream>
#include <unordered_set>
#include "../utils/iostream.h"
#include "set.h"
#include "vector.h"

namespace lib {

    class Coordinates {
    public:
        const int row;
        const int column;

        Coordinates();

        Coordinates(int row, int column);

        bool operator==(const Coordinates &other) const;
    };

}


namespace std {

    template <>
    struct hash<lib::Coordinates> {

        std::size_t operator()(const lib::Coordinates& coordinates) const {
            std::size_t hash = 0;
            hash += coordinates.row;
            hash <<= 32;
            hash += coordinates.column;
            return hash;
        }

    };

}

namespace lib {

    template <typename T>
    class GridIterator;

    template <typename T>
    class ConstGridIterator;

    class GridCoordinatesIterator {
    private:
        const int width;
        const int height;
        int row;
        int column;

        GridCoordinatesIterator(int width, int height);

    public:
        static GridCoordinatesIterator begin(int width, int height);
        static GridCoordinatesIterator end(int width, int height);
        void operator++();
        bool operator!=(const GridCoordinatesIterator& other) const;
        Coordinates operator*();
    };


    class GridCoordinatesSystem {
    private:
        const int width;
        const int height;

    public:
        GridCoordinatesSystem(int width, int height);
        GridCoordinatesIterator begin() const;
        GridCoordinatesIterator end() const;
    };


    template<typename T>
    class Grid {
    private:
        vector<vector<T>> elements;

        bool in_bounds(const Coordinates& coords) const {
            auto [row, column] = coords;
            return row >= 0 && row < height && column >= 0 && column < width;
        }

    public:
        const int width;
        const int height;
        GridCoordinatesSystem coordinates;

        Grid() : width{ 0 }, height{ 0 }, coordinates { 0, 0 } {

        }

        Grid(int width, int height) : width { width }, height { height }, coordinates { width, height } {
            elements.resize(height);
            for (auto& row : elements)
                row.resize(width);
        }

        Grid(std::initializer_list<std::vector<T>> init_list) : width { 0 }, height { 0 }, elements { init_list } {
            const_cast<int&>(width) = init_list.begin()->size();
            const_cast<int&>(height) = init_list.size();
        }

        vector<T>& operator[](int row) {
            return elements[row];
        }

        const vector<T>& operator[](int row) const {
            return elements[row];
        }

        vector<T> row(int i) const {
            return (*this)[i];
        }

        vector<T>& row(int i) {
            return (*this)[i];
        }

        vector<T> column(int j) const {
            vector<T> result;
            for (int row = 0; row < height; row++)
                result.push_back(elements[row][j]);
            return result;
        }

        void set_row(int row, const vector<T>& values) {

        }

        Grid& operator=(const Grid &other) {
            const_cast<int&>(width) = other.width;
            const_cast<int&>(height) = other.height;
            elements = other.elements;
            return *this;
        }

        set<Coordinates> adjacent_neighbors(int row, int column) {
            set<Coordinates> candidates {
                { row - 1, column },
                { row + 1, column },
                { row, column - 1 },
                { row, column + 1 }
            };
            set<Coordinates> result;
            for (auto& neighbor : candidates)
                if (in_bounds(neighbor))
                    result.insert(neighbor);
            return result;
        }

        set<Coordinates> neighbors(int row, int column) const {
            set<Coordinates> result;
            Coordinates a { row - 1, column - 1 };
            if (in_bounds(a))
                result.insert(a);
            Coordinates b { row - 1, column };
            if (in_bounds(b))
                result.insert(b);
            Coordinates c { row - 1, column + 1 };
            if (in_bounds(c))
                result.insert(c);
            Coordinates d = { row, column - 1 };
            if (in_bounds(d))
                result.insert(d);
            Coordinates e { row, column + 1 };
            if (in_bounds(e))
                result.insert(e);
            Coordinates f { row + 1, column - 1 };
            if (in_bounds(f))
                result.insert(f);
            Coordinates g { row + 1, column };
            if (in_bounds(g))
                result.insert(g);
            Coordinates h { row + 1, column + 1};
            if (in_bounds(h))
                result.insert(h);
            return result;
        }

        set<Coordinates> neighbors(const Coordinates& coords) const {
            return neighbors(coords.row, coords.column);
        }

        GridIterator<T> begin() {
            return GridIterator<T>::begin(*this);
        }

        GridIterator<T> end() {
            return GridIterator<T>::end(*this);
        }

        ConstGridIterator<T> begin() const {
            return ConstGridIterator<T>::begin(*this);
        }

        ConstGridIterator<T> end() const {
            return ConstGridIterator<T>::end(*this);
        }

        friend std::ostream& operator<<(std::ostream& stream, const Grid& grid) {
            for (int row = 0; row < grid.height; row++)
                stream << grid[row] << "\n";
            stream << "\n";
            return stream;
        }

    };

    template <typename T>
    using grid = Grid<T>;





    template <typename T>
    class GridIterator {
    private:
        Grid<T>& grid;
        int row;
        int column;

        explicit GridIterator(Grid<T>& grid) : grid { grid } {

        }

    public:
        static GridIterator begin(Grid<T>& grid) {
            GridIterator iterator { grid };
            iterator.row = 0;
            iterator.column = 0;
            return iterator;
        }

        static GridIterator end(Grid<T>& grid) {
            GridIterator iterator { grid };
            iterator.row = grid.height;
            iterator.column = 0;
            return iterator;
        }

        void operator++() {
            column++;
            if (column >= grid.width) {
                row++;
                column = 0;
            }
        }

        bool operator!=(const GridIterator& other) {
            bool eq = (grid.width == other.grid.width
                    && grid.height == other.grid.height
                    && row == other.row
                    && column == other.column);
            return !eq;
        }

        T& operator*() {
            return grid[row][column];
        }

    };



    template <typename T>
    class ConstGridIterator {
    private:
        const Grid<T>& grid;
        int row;
        int column;

        explicit ConstGridIterator(const Grid<T>& grid) : grid { grid } {

        }

    public:
        static ConstGridIterator begin(const Grid<T>& grid) {
            ConstGridIterator iterator { grid };
            iterator.row = 0;
            iterator.column = 0;
            return iterator;
        }

        static ConstGridIterator end(const Grid<T>& grid) {
            ConstGridIterator iterator { grid };
            iterator.row = grid.height;
            iterator.column = 0;
            return iterator;
        }

        void operator++() {
            column++;
            if (column >= grid.width) {
                row++;
                column = 0;
            }
        }

        bool operator!=(const ConstGridIterator& other) {
            bool eq = (grid.width == other.grid.width
                       && grid.height == other.grid.height
                       && row == other.row
                       && column == other.column);
            return !eq;
        }

        const T& operator*() {
            return grid[row][column];
        }

    };

}