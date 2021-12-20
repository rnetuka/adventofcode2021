//
// Created by rnetuka on 15.12.21.
//

#include <cassert>
#include "day14.h"
#include "lib/all.h"

using namespace lib;

namespace Day14 {

    struct Rule {
        string left;
        string right;
    };

    vector<Rule> read_rules() {
        auto lines = File::open("input/day14.txt").read_lines();
        vector<Rule> rules;
        for (auto& line : lines) {
            if (line.contains("->")) {
                auto parts = line.split(" -> ");
                Rule rule{parts[0], parts[1]};
                rules.push_back(rule);
            }
        }
        return rules;
    }

    int solution_1() {
        string polymer = "KHSSCSKKCPFKPPBBOKVF";
        auto rules = read_rules();

        for (int step = 0; step < 10; step++) {
            vector<Rule> applied_rules;
            for (auto& rule : rules)
                if (polymer.contains(rule.left))
                    applied_rules.push_back(rule);

            for (auto& rule : applied_rules) {
                while (polymer.contains(rule.left)) {
                    int i = polymer.index_of(rule.left);
                    polymer = polymer.insert(i, rule.right.lower_case());
                }
            }
            polymer = polymer.upper_case();
        }

        map<char, int> counts;
        for (auto& rule : rules) {
            for (char c : rule.left)
                if (! counts.contains(c))
                    counts[c] = polymer.count(c);
            for (char c : rule.right)
                if (! counts.contains(c))
                    counts[c] = polymer.count(c);
        }

        return max_value(counts) - min_value(counts);
    }

    void print_answers() {
        int answer_1 = solution_1();

        cout << "Day 14\n";
        cout << "  What do you get if you take the quantity of the most common element and subtract the quantity of the"
                " least common element? " << answer_1 << "\n";

        // Check correct answers
        assert(answer_1 == 5656);
    }

}