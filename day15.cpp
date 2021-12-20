//
// Created by rnetuka on 16.12.21.
//

#include <cassert>
#include "day15.h"
#include "lib/all.h"

using namespace lib;

namespace Day15 {

    string node_id(int row, int column) {
        return string(row) + "," + column;
    }

    int solution_1() {
        auto lines = File::open("input/day15.txt").read_lines();

        int width = lines[0].length;
        int height = lines.size() - 1;
        grid<int> grid { width, height };

        for (int row = 0; row < height; row++)
            for (int column = 0; column < width; column++)
                grid[row][column] = atoi(lines[row][column]);

        graph g;

        for (int row = 0; row < height; row++)
            for (int column = 0; column < width; column++)
                g.add(node_id(row, column));

        for (int row = 0; row < height; row++)
            for (int column = 0; column < width; column++) {
                string node = node_id(row, column);
                for (auto [neighbor_row, neighbor_column] : grid.adjacent_neighbors(row, column)) {
                    string neighbor = node_id(neighbor_row, neighbor_column);
                    int length = grid[neighbor_row][neighbor_column];
                    g.connect(node, neighbor, length);
                }
            }

        string start = "0,0";
        string end = node_id(height - 1, width - 1);
        auto path = g.shortest_path(start, end);
        return path.length;
    }

    void print_answers() {
        int answer_1 = solution_1();

        cout << "Day 15\n";
        cout << "  What is the lowest total risk of any path from the top left to the bottom right? " << answer_1 << "\n";

        // Check correct answers
        assert(answer_1 == 441);
    }

}