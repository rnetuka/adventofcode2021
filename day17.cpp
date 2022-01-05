//
// Created by rnetuka on 04.01.22.
//

#include <cassert>
#include "day17.h"
#include "lib/geometry.h"
#include "lib/all.h"

using namespace geom;
using namespace lib;

namespace Day17 {

    struct Probe {
        int x = 0;
        int y = 0;
        int x_velocity;
        int y_velocity;
        operator Point() const {
            return { x, y };
        }
    };

    Rectangle read_input() {
        string input = File::open("input/day17.txt").read();
        auto search = regex::search(input, R"(x=(-?[0-9]+)\.\.(-?[0-9]+), y=(-?[0-9]+)\.\.(-?[0-9]+))");
        int min_x = stoi(search.group(1));
        int max_x = stoi(search.group(2));
        int min_y = stoi(search.group(3));
        int max_y = stoi(search.group(4));
        int width = max_x - min_x;
        int height = max_y - min_y;
        return Rectangle::from({ min_x, max_y }).width(width).height(height);
    }

    const Rectangle target_area = read_input();

    bool try_probe(int x_velocity, int y_velocity) {
        Probe probe { 0, 0, x_velocity, y_velocity };
        while (true) {
            probe.x += probe.x_velocity;
            probe.y += probe.y_velocity;
            if (probe.x_velocity > 0)
                probe.x_velocity--;
            else if (probe.x_velocity < 0)
                probe.x_velocity++;
            probe.y_velocity--;
            if (target_area.contains(probe))
                return true;
            if (probe.y < target_area.min_y())
                return false;
        }
    }

    int solution_1() {
        int result = 0;

        // Optimization
        // consider only X velocities lower than target area max X because otherwise it would just overflew the area in the first step
        for (int x_velocity = 1; x_velocity <= target_area.max_x(); x_velocity++)
            // Experimentally, there are no changes after value 110
            for (int y_velocity = 0; y_velocity < 110; y_velocity++)
                if (try_probe(x_velocity, y_velocity))
                    result = max(result, y_velocity);

        // if Y velocity is 9, the maximum height the probe reaches is 9+8+7+6+5+4+3+2+1, i.e. n(n+1)/2
        return (result * (result + 1)) / 2;
    }

    int solution_2() {
        set<Point> velocities;
        // Optimization
        // consider only X velocities lower than target area max X because otherwise it would just overflew the area in the first step
        for (int x_velocity = 1; x_velocity <= target_area.max_x(); x_velocity++)
            // Experimentally, there are no changes outside interval (-110; 110)
            for (int y_velocity = -110; y_velocity < 110; y_velocity++)
                if (try_probe(x_velocity, y_velocity))
                    velocities.insert({ x_velocity, y_velocity });
        return velocities.size();
    }

    void print_answers() {
        read_input();
        int answer_1 = solution_1();
        int answer_2 = solution_2();

        cout << "Day 17\n";
        cout << "What is the highest y position it reaches on this trajectory?\n";
        cout << answer_1 << "\n";
        cout << "How many distinct initial velocity values cause the probe to be within the target area after any step?\n";
        cout << answer_2 << "\n";

        // Check correct answers
        assert(answer_1 == 5460);
        assert(answer_2 == 3618);
    }

}