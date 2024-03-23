#include <fstream>
#include <utility>
#include <string>
#include <chrono>
#include <cmath>
#include <cstdint>
using namespace std;
using u64 = unsigned long long int;
using grid = pair<u64, u64>;

ofstream fout("hooks.out");
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

void print_grid(grid &grid, string val) {
    fout << endl;

    // first 64 bits of grid
    for (int i = 0; i < 64; i++) {
        if ((i % 9) == 0)
            fout << "  ";

        if (grid.first & (1ull << i)) {
            fout << val << " ";
        } else {
            fout << ". ";
        }

        if ((i % 9) == 8)
            fout << endl;
    }

    // last 17 bits of grid
    for (int i = 0; i < 17; i++) {
        if ((i % 9) == 8)
            fout << "  ";

        if (grid.second & (1ull << i)) {
            fout << val << " ";
        } else {
            fout << ". ";
        }

        if ((i % 9) == 7)
            fout << endl;
    }

    fout << "first: " << grid.first << endl;
    fout << "second: " << grid.second << endl;
    fout << endl;
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

void set_bits(grid &grid, u64 first, u64 second, int shift) {
    grid.first |= first << shift;
    // if we try to shift into index 64 or higher
    if ((msb(first) + shift) > 64) {
        grid.second |= (first >> (64 - shift));
    }
    grid.second |= second << shift;
}

void unset_bits(grid &grid, u64 first, u64 second, int shift) {
    grid.first &= ~(first << shift);
    // if we try to shift into index 64 or higher
    if ((msb(first) + shift) > 64) {
        grid.second |= (first >> (64 - shift));
    }
    grid.second &= ~(second << shift);
}

void set_hook(grid &grid, int x, int y, int hook_size, int rotation) {
    set_bits(
        grid,
        hooks[hook_size-1][rotation][0],
        hooks[hook_size-1][rotation][1],
        (y * 9) + x
    );
}

void unset_hook(grid &grid, int x, int y, int hook_size, int rotation) {
    unset_bits(
        grid,
        hooks[hook_size-1][rotation][0],
        hooks[hook_size-1][rotation][1],
        (y * 9) + x
    );
}

// bool valid(grid &grid, int x, int y, int hook_size, int rotation) {
//     if (x + hook_size > n || y + hook_size > n)
//         return false;
//
//     switch (rotation) {
//         case 0:
//             for (int i = 0; i < hook_size; i++) {
//                 if (grid.values[y+i][x] > 0 || grid.values[y][x+i] > 0) return false;
//             }
//             break;
//         case 1:
//             for (int i = 0; i < hook_size; i++) {
//                 if (grid.values[y+i][x] > 0 || grid.values[y+hook_size-1][x+i] > 0) return false;
//             }
//             break;
//         case 2:
//             for (int i = 0; i < hook_size; i++) {
//                 if (grid.values[y][x+i] > 0 || grid.values[y+i][x+hook_size-1] > 0) return false;
//             }
//             break;
//         case 3:
//             for (int i = 0; i < hook_size; i++) {
//                 if (grid.values[y+i][x+hook_size-1] > 0 || grid.values[y+hook_size-1][x+i] > 0) return false;
//             }
//             break;
//     }
//
//     return true;
// }

// void dfs(grid &grid, int current_hook) {
//     if (current_hook == 0) {
//         print_grid(grid);
//         combos++;
//         return;
//     }
//
//     for (int x = 0; x < n - current_hook + 1; x++) {
//         for (int y = 0; y < n - current_hook + 1; y++) {
//             for (int r = 0; r < 4; r++) {
//                 if (valid(grid, x, y, current_hook, r)) {
//                     set_hook(grid, x, y, current_hook, r);
//
//                     dfs(grid, current_hook - 1);
//
//                     unset_hook(grid, x, y, current_hook, r);
//                 }
//
//                 if (current_hook == 1) {
//                     break;
//                 }
//             }
//         }
//     }
// }

int main() {

    grid grid;
    grid.first = 0ull;
    grid.second = 0ull;

    for (int h = 3; h < 4; h++) {
        for (int x = 0; x < n - h + 1; x++) {
            for (int y = 0; y < n - h + 1; y++) {
                for (int r = 0; r < 4; r++) {
                    set_hook(grid, x, y, h, r);

                    print_grid(grid, "x");

                    unset_hook(grid, x, y, h, r);

                    if (h == 1)
                        break;
                }
            }
        }
    }

    // auto end = chrono::steady_clock::now();
    // chrono::duration<double> duration = end - start;
    // fout << endl;
    // fout << "Total Combinations: " << combos << endl;
    // fout << "Execution time: " << round(duration.count() * 100) / 100 << "s" << endl;
}
