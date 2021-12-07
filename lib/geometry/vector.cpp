//
// Created by rnetuka on 07.12.21.
//

#include <cmath>
#include "vector.h"

namespace geom {

    Vector::Vector() : dx { 0 }, dy { 0 } {

    }

    Vector::Vector(int dx, int dy) : dx { dx }, dy { dy } {

    }

    Vector::Vector(const Point& a, const Point& b) : Vector() {
        const_cast<int&>(dx) = b.x - a.x;
        const_cast<int&>(dy) = b.y - a.y;
    }

    double Vector::length() const {
        return sqrt(pow(dx, 2) + pow(dy, 2));
    }

    Vector Vector::operator+(const Vector& other) const {
        return { dx + other.dx, dy + other.dy };
    }

    Vector Vector::operator*(int c) const {
        return { c * dx, c * dy };
    }

    double Vector::operator*(const Vector& other) const {
        return dx * other.dx + dy * other.dy;
    }

    Vector operator-(const Point& a, const Point& b) {
        return { b, a };
    }

    Point operator+(const Point& point, const Vector& vector) {
        return { point.x + vector.dx, point.y + vector.dy };
    }

}