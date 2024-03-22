#include <iostream>
#include <chrono>
#include <cmath>
#include <cstdint>
using namespace std;
using u64 = unsigned long long int;

struct grid {
    u64 values[2] = {0ull, 1ull};
};
int combos = 0;
auto start = chrono::steady_clock::now();

const int n = 9;
const u64 hooks[n][4][2] = {
    {{1ull, 0ull}, {1ull, 0ull}, {1ull, 0ull}, {1ull, 0ull}},
    {{515ull, 0ull}, {1027ull, 0ull}, {1537ull, 0ull}, {1538ull, 0ull}},
    {{262663ull, 0ull}, {1050631ull, 0ull}, {1835521ull, 0ull}, {1837060ull, 0ull}},
    {{134480399ull, 0ull}, {1075843087ull, 0ull}, {2013528577ull, 0ull}, {2015367176ull, 0ull}},
    {{68853957151ull, 0ull}, {1101663313951ull, 0ull}, {2130438259201ull, 0ull}, {2132455464976ull, 0ull}},
    {{35253226046015ull, 0ull}, {1128103233470527ull, 0ull}, {1090784388710913ull, 0ull}, {2218818768224288ull, 0ull}},
    {{18049651735528063ull, 0ull}, {1128103233470527ull, 0ull}, {2216684295553537ull, 0ull}, {2218818768224288ull, 0ull}},
    {{0ull, 0ull}, {0ull, 0ull}, {0ull, 0ull}, {0ull, 0ull}},
    {{0ull, 0ull}, {0ull, 0ull}, {0ull, 0ull}, {0ull, 0ull}},
};

void print_grid(grid &grid, int val) {
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << "  ";
        for (int j = 0; j < n; j++) {
            int index = i * n + j;
            int board_index = index / 64;
            int bit_index = index % 64;
            if (grid.values[board_index] & (1ull << bit_index)) {
                cout << val << " ";
            } else {
                cout << "0 ";
            }
        }
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

void set_bits(grid &grid, u64 bitmask[], int shift) {
    grid.values[0] |= bitmask[0] << shift;
    // if we try to shift into index 64 or higher
    if ((msb(bitmask[0]) + shift) > 63) {
        cout << "overflow" << endl;
        cout << (bitmask[1] >> (64 - shift)) << endl;
        grid.values[1] |= (bitmask[0] >> (64 - shift));
    }
}

void unset_bits(grid &grid, u64 bitmask, int shift) {
    grid.values[0] &= ~(bitmask << shift);
    // if we try to shift into index 64 or higher
    if ((msb(bitmask) + shift) > 63) {
        grid.values[1] &= ~(bitmask >> (64 - shift));
    }
}

void set_hook(grid &grid, int x, int y, int hook_size, int rotation) {
    set_bits(grid, hooks[hook_size][rotation], (y * 9) + x);
}

void unset_hook(grid &grid, int x, int y, int hook_size, int rotation) {
    unset_bits(grid, hooks[hook_size][rotation], (y * 9) + x);
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

    // int hook_size = 5;
    // int x = 0, y = 0;
    // for (int x = 0; x < n - 6; x++) {
    //     for (int y = 0; y < n - 6; y++) {
            // for (int r = 0; r < 4; r++) {
            //     set_hook(grid, x, y, hook_size-1, r);
            //
            //     print_grid(grid, 1);
            //
            //     unset_hook(grid, x, y, hook_size-1, r);
            // }
    //     }
    // }

    cout << endl;
    u64 bitmask = 
        (1ull << (0 + 0 * n)) |
        (1ull << (1 + 0 * n)) |
        (1ull << (2 + 0 * n)) |
        (1ull << (3 + 0 * n)) |
        (1ull << (4 + 0 * n)) |
        (1ull << (5 + 0 * n)) |
        (1ull << (6 + 0 * n)) |
        (1ull << (7 + 0 * n)) |
        (1ull << (0 + 1 * n)) |
        (1ull << (0 + 2 * n)) |
        (1ull << (0 + 3 * n)) |
        (1ull << (0 + 4 * n)) |
        (1ull << (0 + 5 * n)) |
        (1ull << (0 + 6 * n)) |
        (1ull << (63));
    // set_bits(grid, bitmask, 0);
    print_grid(grid, 1);
    cout << bitmask << endl;

    // auto end = chrono::steady_clock::now();
    // chrono::duration<double> duration = end - start;
    // cout << endl;
    // cout << "Total Combinations: " << combos << endl;
    // cout << "Execution time: " << round(duration.count() * 100) / 100 << "s" << endl;
}
