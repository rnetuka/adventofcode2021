//
// Created by rnetuka on 07.12.21.
//

#include "line_segment.h"

using namespace std;

namespace geom {

    LineSegment::LineSegment(const Point& a, const Point& b) : a { a }, b { b } {

    }

    bool LineSegment::horizontal() {
        return a.y == b.y;
    }

    bool LineSegment::vertical() {
        return a.x == b.x;
    }

    bool LineSegment::contains(const Point& point) const {
        if (point == a || point == b)
            return true;

        //    P = A + t * u
        // -> t * u = P - A
        // -> t1, t2 = (P - A) / u
        Vector u = direction_vector();
        Vector v = point - a;

        double t1 = (double) v.dx / u.dx;
        double t2 = (double) v.dy / u.dy;

        if (u.dx == 0 && v.dx == 0)
            if (t2 > 0 && t2 < 1)
                return true;

        if (u.dy == 0 && v.dy == 0)
            if (t1 > 0 && t1 < 1)
                return true;

        if (t1 == t2 && t1 > 0 && t1 < 1)
            return true;

        return false;
    }

    Vector LineSegment::direction_vector() const {
        return { b - a };
    }

    bool LineSegment::operator==(const LineSegment& other) const {
        return (a == other.a && b == other.b) || (a == other.b && b == other.a);
    }

    LineSegmentBuilder LineSegment::from(const Point& point) {
        return { point };
    }

    LineSegmentBuilder LineSegment::from(int x, int y) {
        return { Point { x, y } };
    }

    LineSegmentBuilder::LineSegmentBuilder(const Point& point) : a { point } {

    }

    LineSegment LineSegmentBuilder::to(const Point& b) const {
        return { a, b };
    }

    LineSegment LineSegmentBuilder::to(int x, int y) const {
        return { a, Point { x, y } };
    }

}