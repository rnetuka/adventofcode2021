//
// Created by rnetuka on 07.12.21.
//

#pragma once

#include "point.h"

namespace geom {

    class Vector {
    public:
        const int dx;
        const int dy;

        Vector();
        Vector(int dx, int dy);
        Vector(const Point& a, const Point& b);

        double length() const;

        Vector operator+(const Vector& other) const;
        Vector operator*(int c) const;
        double operator*(const Vector& other) const;
    };

    Vector operator-(const Point& a, const Point& b);
    Point operator+(const Point& point, const Vector& vector);

}