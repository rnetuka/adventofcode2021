//
// Created by rnetuka on 09.12.21.
//

#include <cassert>
#include "day09.h"
#include "lib/all.h"

using namespace lib;

namespace Day9 {

    class Heightmap {
    private:
        grid<int> data;

    public:
        static Heightmap parse(const vector<string>& lines) {
            Heightmap map;
            int width = lines[0].length;
            int height = lines.size();
            map.data = Grid<int> {width, height };
            for (int row = 0; row < height; row++)
                for (int column = 0; column < width; column++)
                    map.data[row][column] = atoi(lines[row][column]);
            return map;
        }

        optional<int> height(int row, int column) const {
            if (row >= 0 && row < data.height && column >= 0 && column < data.width)
                return data[row][column];
            return std::nullopt;
        }

        int height(const Coordinates& coords) const {
            return *height(coords.row, coords.column);
        }

        vector<int> neighbors(int row, int column) const {
            vector<int> result;

            if (auto neighbor = height(row - 1, column))
                result.push_back(*neighbor);

            if (auto neighbor = height(row, column - 1))
                result.push_back(*neighbor);

            if (auto neighbor = height(row + 1, column))
                result.push_back(*neighbor);

            if (auto neighbor = height(row, column + 1))
                result.push_back(*neighbor);

            return result;
        }

        vector<Coordinates> low_points() const {
            vector<Coordinates> result;
            for (int row = 0; row < data.height; row++)
                for (int column = 0; column < data.width; column++) {
                    int height = data[row][column];
                    if (height < min_element(neighbors(row, column)))
                        result.push_back({ row, column });
                }
            return result;
        }

        set<Coordinates> basin(const Coordinates& low_point) {
            set<Coordinates> result;
            queue<Coordinates> queue { low_point };
            while (! queue.empty()) {
                Coordinates coords = queue.pop();
                result.insert(coords);

                Coordinates neighbor_a { coords.row - 1, coords.column };
                auto height_a = height(neighbor_a.row, neighbor_a.column);
                if (height_a && *height_a < 9)
                    if (! result.contains(neighbor_a))
                        queue.push(neighbor_a);

                Coordinates neighbor_b { coords.row, coords.column - 1 };
                auto height_b = height(neighbor_b.row, neighbor_b.column);
                if (height_b && *height_b < 9)
                    if (! result.contains(neighbor_b))
                        queue.push(neighbor_b);

                Coordinates neighbor_c { coords.row + 1, coords.column };
                auto height_c = height(neighbor_c.row, neighbor_c.column);
                if (height_c && *height_c < 9)
                    if (! result.contains(neighbor_c))
                        queue.push(neighbor_c);

                Coordinates neighbor_d { coords.row, coords.column + 1 };
                auto height_d = height(neighbor_d.row, neighbor_d.column);
                if (height_d && *height_d < 9)
                    if (! result.contains(neighbor_d))
                        queue.push(neighbor_d);
            }
            return result;
        }

    };

    vector<string> read_input() {
        auto lines = File::open("input/day09.txt").read_lines();
        lines.pop_back();   // remove last blank line
        return lines;
    }

    int solution_1() {
        Heightmap map = Heightmap::parse(read_input());
        auto low_points = map.low_points();
        int risk = 0;
        for (auto& coordinates : low_points)
            risk += map.height(coordinates) + 1;
        return risk;
    }

    int solution_2() {
        Heightmap map = Heightmap::parse(read_input());
        auto low_points = map.low_points();
        vector<int> basins;
        for (auto& coordinates : low_points) {
            auto basin = map.basin(coordinates);
            basins.push_back(basin.size());
        }
        basins = reversed(sorted(basins));
        return basins[0] * basins[1] * basins[2];
    }

    void print_answers() {
        int answer_1 = solution_1();
        int answer_2 = solution_2();

        cout << "Day 9\n";
        cout << "  What is the sum of the risk levels of all low points on your heightmap? " << answer_1 << "\n";
        cout << "  What do you get if you multiply together the sizes of the three largest basins? " << answer_2 << "\n";

        // Check correct answers
        assert(answer_1 == 475);
        assert(answer_2 == 1092012);
    }

}