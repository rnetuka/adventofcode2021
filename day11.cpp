//
// Created by rnetuka on 13.12.21.
//

#include <cassert>
#include "day11.h"
#include "lib/all.h"

using namespace lib;

namespace Day11 {

    class Octopus {
    public:
        int energy_level;
        bool flashed;

        Octopus() = default;

        Octopus(int energy_level) {
            this->energy_level = energy_level;
            flashed = false;
        }

        friend ostream& operator<<(ostream& stream, const Octopus& octopus) {
            return stream << octopus.energy_level;
        }

    };

    class OctopusGrid {
    private:
        grid<Octopus> octopuses;

    public:
        OctopusGrid() : octopuses { 10, 10 } {
            auto lines = File::open("input/day11.txt").read_lines();
            lines.pop_back(); // remove last blank line
            for (int row = 0; row < 10; row++)
                for (int column = 0; column < 10; column++)
                    octopuses[row][column] = atoi(lines[row][column]);
        }

        void charge_up(const Coordinates& coords) {
            auto& octopus = octopuses[coords.row][coords.column];
            octopus.energy_level++;
        }

        void flash(const Coordinates& coords) {
            auto [row, column] = coords;
            auto& octopus = octopuses[row][column];
            if (octopus.energy_level > 9 && !octopus.flashed) {
                octopus.flashed = true;
                for (auto& neighbor : octopuses.neighbors(coords))
                    charge_up(neighbor);
                for (auto& neighbor : octopuses.neighbors(coords))
                    flash(neighbor);
            }
        }

        int step() {
            for (auto octopus : octopuses.coordinates)
                charge_up(octopus);

            for (auto octopus : octopuses.coordinates)
                flash(octopus);

            int flashes = 0;

            for (auto& octopus : octopuses) {
                octopus.flashed = false;
                if (octopus.energy_level > 9) {
                    flashes++;
                    octopus.energy_level = 0;
                }
            }
            return flashes;
        }

    };

    int solution_1() {
        OctopusGrid octopuses;
        int flashes = 0;
        for (int step = 0; step < 100; step++)
            flashes += octopuses.step();
        return flashes;
    }

    int solution_2() {
        OctopusGrid octopuses;
        for (int step = 1; true; step++) {
            int flashes = octopuses.step();
            if (flashes == 100)
                return step;
        }
    }

    void print_answers() {
        int answer_1 = solution_1();
        int answer_2 = solution_2();

        cout << "Day 11\n";
        cout << "  How many total flashes are there after 100 steps? " << answer_1 << "\n";
        cout << "  What is the first step during which all octopuses flash? " << answer_2 << "\n";

        // Check correct answers
        assert(answer_1 == 1719);
        assert(answer_2 == 232);
    }

}