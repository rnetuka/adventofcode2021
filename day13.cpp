//
// Created by rnetuka on 14.12.21.
//

#include <cassert>
#include "day13.h"
#include "lib/all.h"

using namespace lib;

namespace Day13 {

    class Paper {
    private:
        int width;
        int height;
        grid<int> data;

    public:
        Paper(int width, int height) {
            this->width = width;
            this->height = height;
            data = grid<int>{ width, height };
        }

        void fold_along_x() {
            int new_width = width / 2;
            grid<int> new_data { new_width, height };

            // left half
            for (int row = 0; row < height; row++)
                for (int column = 0; column < new_width; column++)
                    new_data[row][column] += data[row][column];

            // right half
            for (int row = 0; row < height; row++)
                for (int left_column = 0, right_column = width - 1; right_column > new_width; left_column++, right_column-- )
                    new_data[row][left_column] += data[row][right_column];

            data = new_data;
            width = new_width;
        }

        void fold_along_y() {
            int new_height = height / 2;
            grid<int> new_data { width, new_height };

            // top half
            for (int row = 0; row < new_height; row++)
                for (int column = 0; column < width; column++)
                    new_data[row][column] += data[row][column];

            // bottom half
            for (int top_row = 0, bottom_row = height - 1; bottom_row > new_height; top_row++, bottom_row--)
                for (int column = 0; column < width; column++)
                    new_data[top_row][column] += data[bottom_row][column];

            data = new_data;
            height = new_height;
        }

        int visible_dots() const {
            int dots = 0;
            for (int row = 0; row < height; row++)
                for (int column = 0; column < width; column++)
                    if (data[row][column])
                        dots++;
            return dots;
        }

        auto operator[](int row) -> decltype(data[row]) {
            return data[row];
        }

        friend ostream& operator<<(ostream& stream, const Paper& paper) {
            for (int row = 0; row < paper.height; row++) {
                for (int column = 0; column < paper.width; column++)
                    stream << (paper.data[row][column] ? '#' : ' ');
                stream << "\n";
            }
            return stream;
        }

    };

    Paper read_input() {
        auto lines = File::open("input/day13.txt").read_lines();
        int width;
        int height;

        for (auto& line : lines)
            if (line.starts_with("fold along x")) {
                width = line.split('=')[1] * 2 + 1;
                break;
            }

        for (auto& line : lines)
            if (line.starts_with("fold along y")) {
                height = line.split('=')[1] * 2 + 1;
                break;
            }

        Paper paper { width, height };

        for (auto& line : lines) {
            if (! line.contains(','))
                break;
            auto parts = line.split(',');
            int row = parts[1];
            int column = parts[0];
            paper[row][column] = 1;
        }
        return paper;
    }

    int solution_1() {
        Paper paper = read_input();
        paper.fold_along_x();
        return paper.visible_dots();
    }

    Paper solution_2() {
        Paper paper = read_input();
        auto lines = File::open("input/day13.txt").read_lines();
        for (auto& line : lines)
            if (line.starts_with("fold along ")) {
                char axis = line[length("fold along ")];
                switch (axis) {
                    case 'x':
                        paper.fold_along_x();
                        break;
                    case 'y':
                        paper.fold_along_y();
                        break;
                }
            }
        return paper;
    }

    void print_answers() {
        int answer_1 = solution_1();

        cout << "Day 13\n";
        cout << "How many dots are visible after completing just the first fold instruction on your transparent paper? ";
        cout << answer_1 << "\n";
        cout << "What code do you use to activate the infrared thermal imaging camera system?\n\n";
        cout << solution_2() << "\n";

        // Check correct answers
        assert(answer_1 == 631);
        // Part 2: EFLFJGRF
    }

}