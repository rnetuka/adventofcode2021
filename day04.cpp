/*
 * --- Day 4: Giant Squid ---
 *
 * You're already almost 1.5km (almost a mile) below the surface of the ocean, already so deep that you can't see any
 * sunlight. What you can see, however, is a giant squid that has attached itself to the outside of your submarine.
 *
 * Maybe it wants to play bingo?
 *
 * Bingo is played on a set of boards each consisting of a 5x5 grid of numbers. Numbers are chosen at random, and the
 * chosen number is marked on all boards on which it appears. (Numbers may not appear on all boards.) If all numbers in
 * any row or any column of a board are marked, that board wins. (Diagonals don't count.)
 *
 * The submarine has a bingo subsystem to help passengers (currently, you and the giant squid) pass the time. It
 * automatically generates a random order in which to draw numbers and a random set of boards (your puzzle input). For
 * example:
 * 7,4,9,5,11,17,23,2,0,14,21,24,10,16,13,6,15,25,12,22,18,20,8,19,3,26,1
 *
 * 22 13 17 11  0
 *  8  2 23  4 24
 * 21  9 14 16  7
 *  6 10  3 18  5
 *  1 12 20 15 19
 *
 *  3 15  0  2 22
 *  9 18 13 17  5
 * 19  8  7 25 23
 * 20 11 10 24  4
 * 14 21 16 12  6
 *
 * 14 21 17 24  4
 * 10 16 15  9 19
 * 18  8 23 26 20
 * 22 11 13  6  5
 *  2  0 12  3  7
 *
 * After the first five numbers are drawn (7, 4, 9, 5, and 11), there are no winners, but the boards are marked as
 * follows (shown here adjacent to each other to save space):
 *
 * 22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 *  8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
 * 21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 *  6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 *  1 12 20 15 19        14 21 16 12  6         2  0 12  3  7
 *
 * After the next six numbers are drawn (17, 23, 2, 0, 14, and 21), there are still no winners:
 *
 * 22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 *  8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
 * 21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 *  6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 *  1 12 20 15 19        14 21 16 12  6         2  0 12  3  7
 *
 * Finally, 24 is drawn:
 *
 * 22 13 17 11  0         3 15  0  2 22        14 21 17 24  4
 *  8  2 23  4 24         9 18 13 17  5        10 16 15  9 19
 * 21  9 14 16  7        19  8  7 25 23        18  8 23 26 20
 *  6 10  3 18  5        20 11 10 24  4        22 11 13  6  5
 *  1 12 20 15 19        14 21 16 12  6         2  0 12  3  7
 *
 * At this point, the third board wins because it has at least one complete row or column of marked numbers (in this
 * case, the entire top row is marked: 14 21 17 24 4).
 *
 * The score of the winning board can now be calculated. Start by finding the sum of all unmarked numbers on that board;
 * in this case, the sum is 188. Then, multiply that sum by the number that was just called when the board won, 24, to
 * get the final score, 188 * 24 = 4512.
 *
 * To guarantee victory against the giant squid, figure out which board will win first. What will your final score be if
 * you choose that board?
 *
 * --- Part Two ---
 *
 * On the other hand, it might be wise to try a different strategy: let the giant squid win.
 *
 * You aren't sure how many bingo boards a giant squid could play at once, so rather than waste time counting its arms,
 * the safe thing to do is to figure out which board will win last and choose that one. That way, no matter which boards
 * it picks, it will win for sure.
 *
 * In the above example, the second board is the last to win, which happens after 13 is eventually called and its middle
 * column is completely marked. If you were to keep playing until this point, the second board would have a sum of
 * unmarked numbers equal to 148 for a final score of 148 * 13 = 1924.
 *
 * Figure out which board will win last. Once it wins, what would its final score be?
 */

#include <iostream>
#include <regex>
#include <set>
#include <vector>
#include <numeric>
#include "day04.h"
#include "utils/algorithm.h"
#include "utils/fstream.h"
#include "utils/string.h"

using namespace std;

namespace Day4 {
    int solution_1();
    int solution_2();
}

const int marked = -1;

class BingoBoard {
private:
    const int size = 5;
    vector<int> numbers;

public:
    BingoBoard(vector<int>&& numbers);

    void mark(int number);
    bool check_row(int i) const;
    bool check_column(int i) const;
    bool has_match() const;
    int score() const;
};

BingoBoard::BingoBoard(vector<int>&& numbers) : numbers { move(numbers) } {

}

void BingoBoard::mark(int number) {
    for (auto& square : numbers)
        if (square == number)
            square = marked;
}

bool BingoBoard::check_row(int i) const {
    int offset = i * size;
    return all_of(
        numbers.begin() + offset,
        numbers.begin() + offset + size,
        [](int number) { return number == marked; }
    );
}

bool BingoBoard::check_column(int i) const {
    return numbers[i] == marked
        && numbers[i + size] == marked
        && numbers[i + 2 * size] == marked
        && numbers[i + 3 * size] == marked
        && numbers[i + 4 * size] == marked;
}

bool BingoBoard::has_match() const {
    for (int i = 0; i < size; i++)
        if (check_row(i) || check_column(i))
            return true;
    return false;
}

int BingoBoard::score() const {
    int score = 0;
    for (auto square : numbers)
        if (square != marked)
            score += square;
    return score;
}

class Bingo {
private:
    int round;
    vector<int> numbers;

public:
    const int number;
    const vector<BingoBoard> boards;

    Bingo(vector<int> numbers);

    void join(const BingoBoard& board);
    void next_round();
    operator bool() const;
};

Bingo::Bingo(vector<int> numbers) : number { 0 }, numbers { move(numbers) } {
    round = 0;
}

void Bingo::join(const BingoBoard& board) {
    const_cast<vector<BingoBoard>&>(boards).push_back(board);
}

void Bingo::next_round() {
    const_cast<int&>(number) = numbers.at(round);
    round++;
    for (auto& board : const_cast<vector<BingoBoard>&>(boards))
        board.mark(number);
}

Bingo create_game() {
    auto lines = File::open("input/day04.txt").read_lines();
    vector<int> numbers = split<int>(lines[0], ',');

    Bingo game { numbers };

    for (int i = 2; i < lines.size(); i++) {
        lines[i] = regex_replace(lines[i], regex("  "), " ");
        lines[i] = left_trim(lines[i]);
    }

    int i = 2;
    while (i < lines.size()) {
        vector<int> board = concatenate<int>(
            split<int>(lines[i]),
            split<int>(lines[i + 1]),
            split<int>(lines[i + 2]),
            split<int>(lines[i + 3]),
            split<int>(lines[i + 4])
        );
        game.join(move(board));
        i += 6;
    }
    return game;
}

Bingo::operator bool() const {
    return round < numbers.size();
}

int Day4::solution_1() {
    auto bingo = create_game();
    while (bingo) {
        bingo.next_round();
        for (auto& board : bingo.boards)
            if (board.has_match())
                return bingo.number * board.score();
    }
    return -1;
}

int Day4::solution_2() {
    auto bingo = create_game();

    set<int> remaining_boards;
    for (int id = 0; id < bingo.boards.size(); id++)
        remaining_boards.insert(id);

    const BingoBoard* last_winner = nullptr;

    while (bingo) {
        if (remaining_boards.empty())
            return bingo.number * last_winner->score();

        if (remaining_boards.size() == 1) {
            int id = *remaining_boards.begin();
            last_winner = &bingo.boards[id];
        }

        bingo.next_round();
        for (int id = 0; id < bingo.boards.size(); id++)
            if (remaining_boards.contains(id) && bingo.boards[id].has_match())
                remaining_boards.erase(id);
    }
    return -1;
}

void Day4::print_answers() {
    cout << "Day 4\n";
    cout << "  What will your final score be if you choose that board? " << solution_1() << "\n";
    cout << "  Once it wins, what would its final score be? " << solution_2() << "\n";
}

// Correct answers
// Part 1: 6592
// Part 2: 31755