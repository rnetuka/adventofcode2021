//
// Created by rnetuka on 03.01.22.
//

#include <cassert>
#include "day16.h"
#include "lib/all.h"

using namespace lib;

namespace Day16 {

    enum PacketType {
        OPERATION_SUM = 0,
        OPERATION_MULTIPLY = 1,
        OPERATION_MIN = 2,
        OPERATION_MAX = 3,
        LITERAL = 4,
        OPERATION_GREATER_THAN = 5,
        OPERATION_LESS_THAN = 6,
        OPERATION_EQUALS = 7
    };

    enum LengthType {
        TOTAL_LENGTH = '0',
        N_SUBPACKETS = '1'
    };

    class BitStream {
    private:
        vector<char> data;

        BitStream() = default;

    public:
        BitStream(const string& string) {
            data = string.chars();
        }

        static BitStream from_hex(const string& str) {
            BitStream stream;
            for (char c : str) {
                string s = integer::from_hex(c).bin();
                s = s.prepend('0', 4 - s.length);
                stream.data += s.chars();
            }
            return stream;
        }

        char next() {
            return data.pop_front();
        }

        BitStream next(int n) {
            string s;
            for (int i = 0; i < n; i++)
                s += next();
            return s;
        }

        operator string() const {
            string result;
            for (char c : data)
                result += c;
            return result;
        }

        operator bool() const {
            return !data.empty();
        }

    };

    class Packet {
    public:
        int version;
        int type;
        string data;

        static Packet parse(BitStream& stream) {
            Packet packet;
            packet.version = integer::from_bin(stream.next(3));
            packet.type = integer::from_bin(stream.next(3));
            if (packet.type == LITERAL) {
                while (true) {
                    string s = stream.next(5);
                    packet.data += s;
                    if (s[0] == '0')
                        break;
                }
            } else /* OPERATION */ {
                packet.data = stream;
                char length_type = stream.next();
                switch (length_type) {
                    case TOTAL_LENGTH: {
                        int length = integer::from_bin(stream.next(15));
                        stream.next(length);
                        break;
                    }
                    case N_SUBPACKETS: {
                        int n = integer::from_bin(stream.next(11));
                        for (int i = 0; i < n; i++)
                            Packet::parse(stream);
                        break;
                    }
                }
            }
            return packet;
        }

        long literal_value() const {
            string s;
            for (int i = 0; true; i += 5) {
                s += data.substring(i + 1, i + 1 + 4);
                if (data[i] == '0')
                    break;
            }
            return stol(s, 2);
        }

        vector<Packet> subpackets() const {
            vector<Packet> result;
            BitStream stream { data };
            char length_type = stream.next();
            switch (length_type) {
                case TOTAL_LENGTH: {
                    int length = integer::from_bin(stream.next(15));
                    BitStream substream = stream.next(length);
                    while (substream) {
                        Packet subpacket = Packet::parse(substream);
                        result.push_back(subpacket);
                    }
                    break;
                }
                case N_SUBPACKETS: {
                    int n = integer::from_bin(stream.next(11));
                    for (int i = 0; i < n; i++) {
                        Packet subpacket = Packet::parse(stream);
                        result.push_back(subpacket);
                    }
                    break;
                }
            }
            return result;
        }

        long evaluate() const {
            switch (type) {
                case LITERAL:
                    return literal_value();
                case OPERATION_SUM: {
                    long result = 0;
                    for (auto& packet : subpackets())
                        result += packet.evaluate();
                    return result;
                }
                case OPERATION_MULTIPLY: {
                    long result = 1;
                    for (auto& packet : subpackets())
                        result *= packet.evaluate();
                    return result;
                }
                case OPERATION_MIN: {
                    vector<long> values;
                    for (auto& packet : subpackets())
                        values.push_back(packet.evaluate());
                    return min_element(values);
                }
                case OPERATION_MAX: {
                    vector<long> values;
                    for (auto& packet : subpackets())
                        values.push_back(packet.evaluate());
                    return max_element(values);
                }
                case OPERATION_LESS_THAN: {
                    auto subs = subpackets();
                    long a = subs[0].evaluate();
                    long b = subs[1].evaluate();
                    return a < b;
                }
                case OPERATION_GREATER_THAN: {
                    auto subs = subpackets();
                    long a = subs[0].evaluate();
                    long b = subs[1].evaluate();
                    return a > b;
                }
                case OPERATION_EQUALS: {
                    auto subs = subpackets();
                    long a = subs[0].evaluate();
                    long b = subs[1].evaluate();
                    return a == b;
                }
            }
            return 0;
        }

    };

    int solution_1() {
        string input = File::open("input/day16.txt").read();
        auto stream = BitStream::from_hex(input);
        int sum = 0;
        queue<Packet> queue { Packet::parse(stream) };
        while (queue) {
            Packet p = queue.pop();
            sum += p.version;
            if (p.type != LITERAL)
                queue += p.subpackets();
        }
        return sum;
    }

    long solution_2() {
        string input = File::open("input/day16.txt").read();
        auto stream = BitStream::from_hex(input);
        Packet p = Packet::parse(stream);
        return p.evaluate();
    }

    void print_answers() {
        int answer_1 = solution_1();
        long answer_2 = solution_2();

        cout << "Day 16\n";
        cout << "  What do you get if you add up the version numbers in all packets? \n";
        cout << "  " << answer_1 << "\n";
        cout << "  What do you get if you evaluate the expression represented by your hexadecimal-encoded BITS transmission?\n";
        cout << "  " << answer_2 << "\n";

        // Check correct answers
        assert(answer_1 == 936);
        assert(answer_2 == 6'802'496'672'062L);
    }

}