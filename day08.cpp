//
// Created by rnetuka on 08.12.21.
//

#include <cassert>
#include "day08.h"
#include "lib/all.h"

using namespace lib;

namespace Day8 {

    class Table {
    private:
        map<string, int> table;

    public:
        int& operator[](const string& digit) {
            return table[digit];
        }

        bool decoded(const string& digit) const {
            return table.contains(digit);
        }

        bool decoded(int number) const {
            for (auto& [key, value] : table)
                if (number == value)
                    return true;
            return false;
        }

        string segments_for(int number) const {
            for (auto& [key, value] : table)
                if (number == value)
                    return key;
            return "-";
        }

    };

    /*
     * 0:   Uses a total of 6 segments
     * 1:   Uses a total of 2 segments
     * 2:   Uses a total of 5 segments
     * 3:   Uses a total of 5 segments
     * 4:   Uses a total of 4 segments
     * 5:   Uses a total of 5 segments
     * 6:   Uses a total of 6 segments
     * 7:   Uses a total of 3 segments
     * 8:   Uses a total of 7 segments_for
     * 9:   Uses a total of 6 segments
     */
    vector<int> decode(const string& str) {
        auto parts = str.split(" | ");
        auto signal = parts[0];
        auto out = parts[1];
        auto digits = signal.split();
        for (string& digit : digits)
            digit = sorted(digit);

        Table table;

        // digits taht have unique segment length
        for (string& digit : digits) {
            if (digit.length == 2)
                table[digit] = 1;

            if (digit.length == 3)
                table[digit] = 7;

            if (digit.length == 4)
                table[digit] = 4;

            if (digit.length == 7)
                table[digit] = 8;
        }

        // 1 + three segments_for is 3
        if (table.decoded(1))
            for (string& digit : digits)
                if (! table.decoded(digit))
                    if (digit.length == 5 && digit.contains_all(table.segments_for(1)))
                        table[digit] = 3;

        // 7 + two segments_for is 3
        if (table.decoded(7))
            for (string& digit : digits)
                if (! table.decoded(digit))
                    if (digit.length == 5 && digit.contains_all(table.segments_for(7)))
                        table[digit] = 3;

        // currently have table digits for 1,3,4,7 and 8

        // 4 + two segments_for is 9
        if (table.decoded(4))
            for (string& digit : digits)
                if (! table.decoded(digit))
                    if (digit.length == 6 && digit.contains_all(table.segments_for(4)))
                        table[digit] = 9;

        // 3 + one segment is 9
        if (table.decoded(3))
            for (string& digit : digits)
                if (! table.decoded(digit))
                    if (digit.length == 6 && digit.contains_all(table.segments_for(3)))
                        table[digit] = 9;

        // currently have table digits for 1,3,4,7,8 and 9

        // segments_for of total length of 6 that is not 9, is either 0 or 6
        // if it decoded segments_for for 1 or 7, it is 0
        if (table.decoded(9))
            for (string& digit : digits)
                if (!table.decoded(digit))
                    if (digit.length == 6 && digit != table.segments_for(9))
                        if (table.decoded(1) || table.decoded(7))
                            if (digit.contains_all(table.segments_for(1)) || digit.contains_all(table.segments_for(7)))
                                table[digit] = 0;
                            else
                                table[digit] = 6;

        // currently have table digits for 0,1,3,4,6,7,8 and 9

        // 5 + one segment is either 6 or 9
        if (table.decoded(9))
            for (string& digit : digits)
                if (!table.decoded(digit)) {
                    if (digit.length == 5)
                        if (table.decoded(6) || table.decoded(9))
                            if (table.segments_for(6).contains_all(digit) || table.segments_for(9).contains_all(digit))
                                table[digit] = 5;
                            else
                                table[digit] = 2;
            }

        vector<string> out_parts = out.split();
        for (string& digit : out_parts)
            digit = sorted(digit);
        vector<int> result = transform<int>(out_parts, [&table](const string& encoded) { return table[encoded]; });
        return result;
    }

    int solution_1() {
        auto lines = File::open("input/day08.txt").read_lines();
        int count = 0;
        for (string& line : lines)
            if (! line.empty()) {
                vector<int> output = decode(line);
                for (int digit : output)
                    if (digit == 1 || digit == 4 || digit == 7 || digit == 8)
                        count++;
            }
        return count;
    }

    int solution_2() {
        auto lines = File::open("input/day08.txt").read_lines();
        int result = 0;
        for (string& line : lines)
            if (! line.empty()) {
                vector<int> output = decode(line);
                int digits = output[0] * 1000;
                digits += output[1] * 100;
                digits += output[2] * 10;
                digits += output[3];
                result += digits;
            }
        return result;
    }

    void print_answers() {
        int answer_1 = solution_1();
        int answer_2 = solution_2();

        cout << "Day 8\n";
        cout << "  In the output values, how many times do digits 1, 4, 7, or 8 appear? " << answer_1 << "\n";
        cout << "  What do you get if you add up all of the output values? " << answer_2 << "\n";

        // Check correct answers
        assert(answer_1 == 387);
        assert(answer_2 == 986034);
    }

}