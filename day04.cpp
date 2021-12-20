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

#include <cassert>
#include "day04.h"
#include "lib/all.h"

using namespace lib;

namespace Day4 {

    const int marked = -1;


    class BingoBoard {
    private:
        static const int size = 5;
        grid<int> numbers;

    public:
        BingoBoard(const grid<int>& numbers) : numbers { numbers } {

        }

        void mark(int number) {
            for (int& square : numbers)
                if (square == number)
                    square = marked;
        }

        bool check_row(int i) const {
            return numbers.row(i).all_of([](int number) { return number == marked; });
        }

        bool check_column(int j) const {
            return numbers.column(j).all_of([](int number) { return number == marked; });
        }

        bool has_match() const {
            for (int i = 0; i < size; i++)
                if (check_row(i) || check_column(i))
                    return true;
            return false;
        }

        int score() const {
            int score = 0;
            for (int square : numbers)
                if (square != marked)
                    score += square;
            return score;
        }

    };


    class Bingo {
    private:
        vector<int> numbers;
        int round;

    public:
        vector<BingoBoard> boards;

        Bingo(const vector<int>& numbers) : numbers { numbers } {
            round = 0;
        }

        void join(const BingoBoard& board) {
            boards.push_back(board);
        }

        int next_round() {
            int number = numbers[round];
            round++;
            for (auto& board : boards)
                board.mark(number);
            return number;
        }

        operator bool() const {
            return round < numbers.size();
        }

    };


    Bingo create_game() {
        auto lines = File::open("input/day04.txt").read_lines();
        vector<int> numbers = lines[0].split<int>(',');

        Bingo game { numbers };

        for (int i = 2; i < lines.size(); i++) {
            lines[i] = lines[i].replace_all("  ", " ");
            lines[i] = lines[i].left_trim();
        }

        int width = 5;
        int height = 5;

        int i = 2;
        while (i < lines.size()) {
            grid<int> board { width, height };
            board[0] = lines[i].split<int>();
            board[1] = lines[i + 1].split<int>();
            board[2] = lines[i + 2].split<int>();
            board[3] = lines[i + 3].split<int>();
            board[4] = lines[i + 4].split<int>();
            game.join(board);
            i += 6;
        }
        return game;
    }

    int solution_1() {
        auto bingo = create_game();
        while (bingo) {
            int number = bingo.next_round();
            for (auto& board : bingo.boards)
                if (board.has_match())
                    return number * board.score();
        }
        return -1;
    }

    int solution_2() {
        auto bingo = create_game();

        while (bingo) {
            int number = bingo.next_round();

            if (bingo.boards.size() == 1 && bingo.boards[0].has_match())
                return number * bingo.boards[0].score();

            bingo.boards.erase_if([](auto& board) { return board.has_match(); });
        }
        return -1;
    }

    void print_answers() {
        int answer_1 = solution_1();
        int answer_2 = solution_2();

        cout << "Day 4\n";
        cout << "  What will your final score be if you choose that board? " << answer_1 << "\n";
        cout << "  Once it wins, what would its final score be? " << answer_2 << "\n";

        // Check correct answers
        assert(answer_1 == 6592);
        assert(answer_2 == 31755);
    }

}