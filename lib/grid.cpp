//
// Created by rnetuka on 09.12.21.
//

#include "grid.h"

namespace lib {

    Coordinates::Coordinates() : row { 0 }, column { 0 } {

    }

    Coordinates::Coordinates(int row, int column) : row { row }, column { column } {

    }

    bool Coordinates::operator==(const Coordinates& other) const {
        return row == other.row && column == other.column;
    }

    GridCoordinatesIterator::GridCoordinatesIterator(int width, int height) : width { width }, height { height } {

    }

    GridCoordinatesIterator GridCoordinatesIterator::begin(int width, int height) {
        GridCoordinatesIterator iterator { width, height };
        iterator.row = 0;
        iterator.column = 0;
        return iterator;
    }

    GridCoordinatesIterator GridCoordinatesIterator::end(int width, int height) {
        GridCoordinatesIterator iterator { width, height };
        iterator.row = height;
        iterator.column = 0;
        return iterator;
    }

    void GridCoordinatesIterator::operator++() {
        column++;
        if (column >= width) {
            row++;
            column = 0;
        }
    }

    bool GridCoordinatesIterator::operator!=(const GridCoordinatesIterator& other) const {
        bool eq = (width == other.width && height == other.height && row == other.row && column == other.column);
        return !eq;
    }

    Coordinates GridCoordinatesIterator::operator*() {
        return { row, column };
    }

    GridCoordinatesSystem::GridCoordinatesSystem(int width, int height) : width { width }, height { height } {

    }

    GridCoordinatesIterator GridCoordinatesSystem::begin() const {
        return GridCoordinatesIterator::begin(width, height);
    }

    GridCoordinatesIterator GridCoordinatesSystem::end() const {
        return GridCoordinatesIterator::end(width, height);
    }

}