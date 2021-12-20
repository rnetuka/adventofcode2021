//
// Created by rnetuka on 07.12.21.
//

#pragma once

#include <unordered_set>

namespace geom {

    class Point {
    public:
        const int x;
        const int y;

        Point();
        Point(int x, int y);

        bool operator==(const Point& other) const;
        Point& operator=(const Point& other);
    };

}

template <>
struct std::hash<geom::Point> {

    std::size_t operator()(const geom::Point& point) const {
        std::size_t hash = 0;
        hash += point.x;
        hash <<= 32;
        hash += point.y;
        return hash;
    }

};