/*
 * --- Day 5: Hydrothermal Venture ---
 *
 * You come across a field of hydrothermal vents on the ocean floor! These vents constantly produce large, opaque
 * clouds, so it would be best to avoid them if possible.
 *
 * They tend to form in lines; the submarine helpfully produces a list of nearby lines of vents (your puzzle input) for
 * you to review. For example:
 * - 0,9 -> 5,9
 * - 8,0 -> 0,8
 * - 9,4 -> 3,4
 * - 2,2 -> 2,1
 * - 7,0 -> 7,4
 * - 6,4 -> 2,0
 * - 0,9 -> 2,9
 * - 3,4 -> 1,4
 * - 0,0 -> 8,8
 * - 5,5 -> 8,2
 *
 * Each line of vents is given as a line segment in the format x1,y1 -> x2,y2 where x1,y1 are the coordinates of one end
 * the line segment and x2,y2 are the coordinates of the other end. These line segments include the points at both ends.
 *
 * In other words:
 * - An entry like 1,1 -> 1,3 covers points 1,1, 1,2, and 1,3.
 * - An entry like 9,7 -> 7,7 covers points 9,7, 8,7, and 7,7.
 *
 * For now, only consider horizontal and vertical lines: lines where either x1 = x2 or y1 = y2.
 *
 * So, the horizontal and vertical lines from the above list would produce the following diagram:
 * .......1..
 * ..1....1..
 * ..1....1..
 * .......1..
 * .112111211
 * ..........
 * ..........
 * ..........
 * ..........
 * 222111....
 *
 * In this diagram, the top left corner is 0,0 and the bottom right corner is 9,9. Each position is shown as the number
 * of lines which cover that point or . if no line covers that point. The top-left pair of 1s, for example, comes from
 * 2,2 -> 2,1; the very bottom row is formed by the overlapping lines 0,9 -> 5,9 and 0,9 -> 2,9.
 *
 * To avoid the most dangerous areas, you need to determine the number of points where at least two lines overlap. In
 * the above example, this is anywhere in the diagram with a 2 or larger - a total of 5 points.
 *
 * Consider only horizontal and vertical lines. At how many points do at least two lines overlap?
 *
 * --- Part Two ---
 *
 * Unfortunately, considering only horizontal and vertical lines doesn't give you the full picture; you need to also
 * consider diagonal lines.
 *
 * Because of the limits of the hydrothermal vent mapping system, the lines in your list will only ever be horizontal,
 * vertical, or a diagonal line at exactly 45 degrees. In other words:
 * - An entry like 1,1 -> 3,3 covers points 1,1, 2,2, and 3,3.
 * - An entry like 9,7 -> 7,9 covers points 9,7, 8,8, and 7,9.
 *
 * Considering all lines from the above example would now produce the following diagram:
 * 1.1....11.
 * .111...2..
 * ..2.1.111.
 * ...1.2.2..
 * .112313211
 * ...1.2....
 * ..1...1...
 * .1.....1..
 * 1.......1.
 * 222111....
 *
 * You still need to determine the number of points where at least two lines overlap. In the above example, this is
 * still anywhere in the diagram with a 2 or larger - now a total of 12 points.
 *
 * Consider all of the lines. At how many points do at least two lines overlap?
 */

#include <iostream>
#include <unordered_set>
#include <vector>
#include "day05.h"
#include "lib/geometry.h"
#include "utils/fstream.h"
#include "utils/string.h"

using namespace geom;
using namespace std;

namespace Day5 {
    LineSegment parse(const string& str);
    vector<LineSegment> read_input();
    int solution_1();
    int solution_2();
}

LineSegment Day5::parse(const string& string) {
    auto points = split(string, " -> ");
    auto a = split<int>(points[0], ',');
    auto b = split<int>(points[1], ',');
    return LineSegment::from(a[0], a[1]).to(b[0], b[1]);
}

vector<LineSegment> Day5::read_input() {
    auto lines = File::open("input/day05.txt").read_lines();
    vector<LineSegment> line_segments;
    for (string& line : lines)
        if (! line.empty())
            line_segments.push_back(Day5::parse(line));
    return line_segments;
}

vector<Point> points_of(const LineSegment& line_segment) {
    // Line segments in this puzzle are either horizontal (dx = +-1, dy = 0), vertical (dx = 0, dy = +-1) or
    // diagonal (+-dx = +-dy). Direction vector can therefore be normalized to a size of 1
    Vector v = line_segment.direction_vector();
    int dx = v.dx / max(abs(v.dx), abs(v.dy));
    int dy = v.dy / max(abs(v.dx), abs(v.dy));
    vector<Point> points;
    Point point = line_segment.a;
    while (point != line_segment.b) {
        points.push_back(point);
        point = point + Vector { dx, dy };
    }
    points.push_back(line_segment.b);
    return points;
}

int Day5::solution_1() {
    vector<LineSegment> line_segments = read_input();
    unordered_set<Point> points;
    unordered_set<Point> overlaps;
    for (auto& line_segment : line_segments)
        if (line_segment.horizontal() || line_segment.vertical()) {
            vector<Point> line_segment_points = points_of(line_segment);
            for (auto& point : line_segment_points) {
                if (points.contains(point))
                    overlaps.insert(point);
                points.insert(point);
            }
        }
    return overlaps.size();
}

int Day5::solution_2() {
    vector<LineSegment> line_segments = read_input();
    unordered_set<Point> points;
    unordered_set<Point> overlaps;
    for (auto& line_segment : line_segments) {
        vector<Point> line_segment_points = points_of(line_segment);
        for (auto& point : line_segment_points) {
            if (points.contains(point))
                overlaps.insert(point);
            points.insert(point);
        }
    }
    return overlaps.size();
}

void Day5::print_answers() {
    cout << "Day 5\n";
    cout << "  At how many points do at least two lines overlap? " << solution_1() << "\n";
    cout << "  At how many points do at least two lines overlap? " << solution_2() << "\n";
}

// Correct answers
// Part 1: 5608
// Part 2: 20299