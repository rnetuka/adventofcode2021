#include "lib/iostream.h"
#include "lib/string.h"
#include "solutions.h"

using namespace lib;

int main(int argc, char** argv) {
    cout << "Advent of Code 2021\n\n";
    if (argc == 2) {
        int day = string(argv[1]).substring(3);
        switch (day) {
            case 1:  Day1::print_answers(); break;
            case 2:  Day2::print_answers(); break;
            case 3:  Day3::print_answers(); break;
            case 4:  Day4::print_answers(); break;
            case 5:  Day5::print_answers(); break;
            case 6:  Day6::print_answers(); break;
            case 7:  Day7::print_answers(); break;
            case 8:  Day8::print_answers(); break;
            case 9:  Day9::print_answers(); break;
            case 10: Day10::print_answers(); break;
            case 11: Day11::print_answers(); break;
            case 13: Day13::print_answers(); break;
            case 14: Day14::print_answers(); break;
            case 15: Day15::print_answers(); break;
            case 16: Day16::print_answers(); break;
        }
    }

}