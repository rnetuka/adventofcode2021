//
// Created by rnetuka on 04.01.22.
//

#pragma once

#include "point.h"

namespace geom {

    class RectangleBuilder;


    class Rectangle {
    private:
        Point start;
        int width;
        int height;

    public:
        static RectangleBuilder from(const Point& point);

        bool contains(const Point& point) const;
        int min_x() const;
        int max_x() const;
        int min_y() const;
        int max_y() const;

        friend class RectangleBuilder;
    };


    class RectangleBuilder {
    private:
        Point from;
        int rectangle_width;
        int rectangle_height;

    public:
        RectangleBuilder width(int width);
        RectangleBuilder height(int height);
        operator Rectangle() const;

        friend class Rectangle;
    };

}
