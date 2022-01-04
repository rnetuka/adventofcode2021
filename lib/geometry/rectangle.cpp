//
// Created by rnetuka on 04.01.22.
//

#include "rectangle.h"

namespace geom {

    bool Rectangle::contains(const Point& point) const {
        return point.x >= min_x()
            && point.x <= max_x()
            && point.y >= min_y()
            && point.y <= max_y();
    }

    int Rectangle::min_x() const {
        return start.x;
    }

    int Rectangle::max_x() const {
        return start.x + width;
    }

    int Rectangle::min_y() const {
        return start.y - height;
    }

    int Rectangle::max_y() const {
        return start.y;
    }

    RectangleBuilder Rectangle::from(const Point& point) {
        RectangleBuilder builder;
        builder.from = point;
        return builder;
    }

    RectangleBuilder RectangleBuilder::width(int width) {
        rectangle_width = width;
        return *this;
    }

    RectangleBuilder RectangleBuilder::height(int height) {
        rectangle_height = height;
        return *this;
    }

    RectangleBuilder::operator Rectangle() const {
        Rectangle rectangle;
        rectangle.start = from;
        rectangle.width = rectangle_width;
        rectangle.height = rectangle_height;
        return rectangle;
    }

}