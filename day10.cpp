//
// Created by rnetuka on 10.12.21.
//

#include <cassert>
#include "day10.h"
#include "lib/all.h"

using namespace lib;

namespace Day10 {

    map<char, char> pairs {
        { '(', ')' },
        { '[', ']' },
        { '{', '}' },
        { '<', '>' }
    };

    bool opening_char(char c) {
        return pairs.contains(c);
    }

    struct Analyze {
        optional<char> closing_char;
        string complete_string;

        bool corrupted() const {
            return closing_char.has_value();
        }
    };

    Analyze analyze(const string& str) {
        Analyze result;
        stack<char> opening_chars;
        for (char c : str)
            if (opening_char(c))
                opening_chars.push(c);
            else {
                char opening_char = opening_chars.pop();
                char closing_char = c;
                if (pairs[opening_char] != closing_char) {
                    result.closing_char = closing_char;
                    return result;
                }
            }
        while (opening_chars) {
            char opening_char = opening_chars.pop();
            char closing_char = pairs[opening_char];
            result.complete_string += closing_char;
        }
        return result;
    }

    int solution_1() {
        vector<string> lines = File::open("input/day10.txt").read_lines();
        map<char, int> score {
            { ')', 3 },
            { ']', 57 },
            { '}', 1197 },
            { '>', 25137 }
        };
        int points = 0;
        for (string& line : lines) {
            auto result = analyze(line);
            if (result.corrupted())
                points += score[*result.closing_char];
        }
        return points;
    }

    long solution_2() {
        vector<string> lines = File::open("input/day10.txt").read_lines();
        map<char, int> score {
            { ')', 1 },
            { ']', 2 },
            { '}', 3 },
            { '>', 4 }
        };
        vector<long> scores;
        for (string& line : lines) {
            auto result = analyze(line);
            if (! result.corrupted()) {
                long points = 0;
                for (char c : result.complete_string) {
                    points *= 5;
                    points += score[c];
                }
                scores.push_back(points);
            }
        }
        scores = sorted(scores);
        return scores[scores.size() / 2];
    }

    void print_answers() {
        int answer_1 = solution_1();
        long answer_2 = solution_2();

        cout << "Day 10\n";
        cout << "  What is the total syntax error score for those errors? " << answer_1 << "\n";
        cout << "  What is the middle score? " << answer_2 << "\n";

        // Check correct answers
        assert(answer_1 == 415953);
        assert(answer_2 == 2292863731);
    }

    // Correct answers
    // Part 1: 415953
    // Part 2: 2292863731

}