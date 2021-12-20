//
// Created by rnetuka on 08.12.21.
//

#include <cassert>
#include "day06.h"
#include "lib/all.h"

using namespace lib;

namespace Day6 {

    vector<int> read_input() {
        string line = File::open("input/day06.txt").read();
        return line.split<int>(',');
    }

    int solution_1() {
        vector<int> fish = read_input();
        for (int day = 0; day < 80; day++) {
            int size = fish.size();
            for (int i = 0; i < size; i++)
                if (fish[i] == 0) {
                    fish[i] = 6;
                    fish.push_back(8);
                } else
                    fish[i] -= 1;
        }
        return fish.size();
    }

    void print_answers() {
        int answer_1 = solution_1();

        cout << "Day 6\n";
        cout << "  How many lanternfish would there be after 80 days? " << answer_1 << "\n";

        // Check correct answers
        assert(answer_1 == 351092);
    }

}