#include <iostream>
#include <utility>
#include <string>
#include <chrono>
#include <cmath>
#include <cstdint>
using namespace std;
using u64 = unsigned long long int;
using bitboard = pair<u64, u64>;
using state = bitboard[9];

// ofstream cout("hooks.out");
int combos = 0;
auto start = chrono::steady_clock::now();

const int n = 9;
const u64 hooks[n][4][2] = {
    {{1ull, 0ull}, {1ull, 0ull}, {1ull, 0ull}, {1ull, 0ull}},
    {{515ull, 0ull}, {1027ull, 0ull}, {1537ull, 0ull}, {1538ull, 0ull}},
    {{262663ull, 0ull}, {1050631ull, 0ull}, {1835521ull, 0ull}, {1837060ull, 0ull}},
    {{134480399ull, 0ull}, {1075843087ull, 0ull}, {2013528577ull, 0ull}, {2015367176ull, 0ull}},
    {{68853957151ull, 0ull}, {1101663313951ull, 0ull}, {2130438259201ull, 0ull}, {2132455464976ull, 0ull}},
    {{35253226046015ull, 0ull}, {1128103233470527ull, 0ull}, {2216684295553537ull, 0ull}, {2218818768224288ull, 0ull}},
    {{18049651735528063ull, 0ull}, {1155177711073788031ull, 0ull}, {2287863863930257921ull, 0ull}, {2290084817171152960ull, 0ull}},
    {{9241421688590303999ull, 0ull}, {2310355422147576063ull, 64ull}, {9241421688590303745ull, 127ull}, {11533727459002351744ull, 127ull}},
    {{9241421688590304255ull, 256ull}, {4620710844295152127ull, 65664ull}, {9241421688590303745ull, 130816ull}, {4620710844295151872ull, 130944ull}},
};

void print_bitboard(bitboard &bb, string val) {
    cout << endl;

    // first 64 bits of bitboard
    for (int i = 0; i < 64; i++) {
        if ((i % 9) == 0)
            cout << "  ";

        if (bb.first & (1ull << i)) {
            cout << val << " ";
        } else {
            cout << ". ";
        }

        if ((i % 9) == 8)
            cout << endl;
    }

    // last 17 bits of bitboard
    for (int i = 0; i < 17; i++) {
        if ((i % 9) == 8)
            cout << "  ";

        if (bb.second & (1ull << i)) {
            cout << val << " ";
        } else {
            cout << ". ";
        }

        if ((i % 9) == 7)
            cout << endl;
    }

    cout << "first: " << bb.first << endl;
    cout << "second: " << bb.second << endl;
    cout << endl;
}

void print_state(state &s) {
    cout << endl;

    // first 64 bits of bitboard
    for (int i = 0; i < 64; i++) {
        if ((i % 9) == 0)
            cout << "  ";

        bool found = false;
        for (int j = 0; j < 9; j++) {
            if (s[j].first & (1ull << i)) {
                cout << j + 1 << " ";
                found = true;
            }
        }
        if (!found)
            cout << ". ";

        if ((i % 9) == 8)
            cout << endl;
    }

    // last 17 bits of bitboard
    for (int i = 0; i < 17; i++) {
        if ((i % 9) == 8)
            cout << "  ";

        bool found = false;
        for (int j = 0; j < 9; j++) {
            if (s[j].second & (1ull << i)) {
                cout << j + 1 << " ";
                found = true;
            }
        }
        if (!found)
            cout << ". ";

        if ((i % 9) == 7)
            cout << endl;
    }
}

int msb(u64 n) {
    if (n == 0)
        return 0;

    int msb = 0;
    while (n != 0) {
        n >>= 1;
        msb++;
    }
    return msb;
}

int bitstring_length(u64 n) {
    if (n == 0)
        return 1;
    int length = 0;
    while (n) {
        length++;
        n >>= 1;
    }
    return length;
}

void set_bits(bitboard &bb, u64 first, u64 second, int shift) {
    // if there's no overflow for first
    if (shift < 64)
        bb.first |= first << shift;
    // if we try to shift into index 64 or hibbher
    if ((msb(first) + shift) > 64) {
        cout << (first >> (shift - 64)) << endl;
        bb.second |= (first >> (64 - shift));
    }
    bb.second |= second << shift;
}

void unset_bits(bitboard &bb, u64 first, u64 second, int shift) {
    bb.first &= ~(first << shift);
    // if we try to shift into index 64 or hibbher
    if ((msb(first) + shift) > 64) {
        bb.second &= ~(first >> (64 - shift));
    }
    bb.second &= ~(second << shift);
}

void set_hook(bitboard &bb, int x, int y, int h, int r) {
    set_bits(
        bb,
        hooks[h-1][r][0],
        hooks[h-1][r][1],
        (y * 9) + x
    );
}

void unset_hook(bitboard &bb, int x, int y, int h, int r) {
    unset_bits(
        bb,
        hooks[h-1][r][0],
        hooks[h-1][r][1],
        (y * 9) + x
    );
}

bool valid(state &s, int x, int y, int h, int r) {
    // copy hook onto new bitboard
    bitboard hook;

    set_hook(hook, x, y, h, r);

    // check bitboards before
    for (int i = 0; i < h - 1; i++) {
        if (hook.first & s[i].first || hook.second & s[i].second)
            return false;
    }
    // check bitboards after
    for (int i = h; i < 9; i++) {
        if (hook.first & s[i].first || hook.second & s[i].second)
            return false;
    }

    return true;
}

// void dfs(state &s, int h) {
//     if (h == 0) {
//         // print_state(s);
//         combos++;
//         return;
//     }
//
//     for (int x = 0; x < n - h + 1; x++) {
//         for (int y = 0; y < n - h + 1; y++) {
//             for (int r = 0; r < 1; r++) {
//                 if (valid(s, x, y, h, r)) {
//                     set_hook(s[h-1], x, y, h, r);
//
//                     dfs(s, h - 1);
//
//                     unset_hook(s[h-1], x, y, h, r);
//                 }
//
//                 if (h == 1) {
//                     break;
//                 }
//             }
//         }
//     }
// }

void test(int h) {
    bitboard bb;

    // for (int x = 0; x < n - h + 1; x++) {
    //     for (int y = 0; y < n - h + 1; y++) {
    //         for (int r = 0; r < 1; r++) {
    //             set_hook(bb, x, y, h, r);
    //
    //             print_bitboard(bb, "*");
    //             cout << "x: " << x << endl;
    //             cout << "y: " << y << endl;
    //
    //             unset_hook(bb, x, y, h, r);
    //         }
    //     }
    // }
    set_hook(bb, 0, 8, 1, 0);
    print_bitboard(bb, "*");
}

int main() {
    state s;

    // dfs(s, n);
    test(1);

    // auto end = chrono::steady_clock::now();
    // chrono::duration<double> duration = end - start;
    // cout << "Total Combinations: " << combos << endl;
    // cout << "Execution time: " << round(duration.count() * 100) / 100 << "s" << endl;
    //
    // 1 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    //
    // 1
    //
    // 0 0 0 0 0 0 0 0 
    // 1 1 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    //
    // fin ifstream("black_pawns");
    //
    // steps
    // 1. get index i of most significant bit
    // 2. if index % 8 == 0
    //       check dowm and right
    //          set_bit(index + 8)
    //          set_bit(index + 9)
    //    else if index % 8 == 7
    //          set_bit(index + 7)
    //          set_bit(index + 8)
    //    else
    //          set_bit(index + 7)
    //          set_bit(index + 8)
    //          set_bit(index + 9)
    // fout << bitboard << endl;
    //
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    //
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 1 1 1 1 1 1 1 1
    // 0 0 0 0 0 0 0 0 
    //
    // 0 0 0 0 0 0 0 0 
    // 1 1 1 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    //
    // 0 0 0 0 0 0 0 0 
    // 1 1 1 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    // 0 0 0 0 0 0 0 0 
    //
    // 1 0 1 1
    //
    // 0 1 1 0
    //
    //
    //
    // 1 0 1 1 &
    // 0 1 1 0
    // 0 0 1 0 
    //
    // 1 0 1 1 |
    // 0 1 1 0
    // 1 1 1 1 
    //
    // int x = 1011;
    // x &= 0110;
    //
    // cout << x << endl;
    //
    //
}
