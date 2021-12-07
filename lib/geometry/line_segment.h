//
// Created by rnetuka on 07.12.21.
//

#pragma once

#include <optional>
#include "point.h"
#include "vector.h"

namespace geom {

    class LineSegmentBuilder;



    class LineSegment {
    private:
        LineSegment(const Point& a, const Point& b);

    public:
        const Point a;
        const Point b;

        LineSegment();

        bool horizontal();
        bool vertical();
        bool contains(const Point& point) const;
        Vector direction_vector() const;

        bool operator==(const LineSegment& other) const;

        static LineSegmentBuilder from(const Point& point);
        static LineSegmentBuilder from(int x, int y);

        friend class LineSegmentBuilder;
    };



    class LineSegmentBuilder {
    private:
        const Point a;

        LineSegmentBuilder(const Point& point);

    public:
        LineSegment to(const Point& point) const;
        LineSegment to(int x, int y) const;

        friend class LineSegment;
    };

}
