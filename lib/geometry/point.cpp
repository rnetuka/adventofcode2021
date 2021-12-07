//
// Created by rnetuka on 07.12.21.
//

#include "point.h"

namespace geom {

    Point::Point() : x { 0 }, y { 0 } {

    }

    Point::Point(int x, int y) : x { x }, y { y } {

    }

    bool Point::operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    Point& Point::operator=(const Point& other) {
        const_cast<int&>(x) = other.x;
        const_cast<int&>(y) = other.y;
        return *this;
    }

}