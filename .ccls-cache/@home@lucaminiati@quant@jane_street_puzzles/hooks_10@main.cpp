#include <iostream>
#include <chrono>
#include <cmath>
#include <cstdint>
using namespace std;
using u64 = long long int;

const int n = 9;
struct grid {
    u64 values[2] = {0ULL, 0ULL};
};
int combos = 0;
auto start = chrono::steady_clock::now();

void print_grid(grid &grid, int val) {
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << "  ";
        for (int j = 0; j < n; j++) {
            int index = i * n + j;
            int board_index = index / 64;
            int bit_index = index % 64;
            uint64_t bit = 1;
            if ((grid.values[board_index] & (bit << bit_index)) > 0) {
                cout << val << " ";
            } else {
                cout << "0 ";
            }
        }
        cout << endl;
    }
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

void set_bits(grid &grid, u64 bitmask, int hook_size, int shift=0) {
    grid.values[0] |= (bitmask << shift);
    // if we overflow into the second int
    if ((bitmask << shift) > 9223372036854775808ull) {

    }
}

void set_hook(grid &grid, int x, int y, int hook_size, int rotation) {
    switch (rotation) {
        case 0:
            grid.values[0] |= (2130438259201ull << x);
            break;
        case 1:
            for (int i = 0; i < hook_size; i++) {
                // grid.values[y+i][x] = hook_size;
                // grid.values[y+hook_size-1][x+i] = hook_size;
            }
            break;
        case 2:
            for (int i = 0; i < hook_size; i++) {
                // grid.values[y][x+i] = hook_size;
                // grid.values[y+i][x+hook_size-1] = hook_size;
            }
            break;
        case 3:
            for (int i = 0; i < hook_size; i++) {
                // grid.values[y+hook_size-1][x+i] = hook_size;
                // grid.values[y+i][x+hook_size-1] = hook_size;
            }
            break;
    }
}

// void unset_hook(grid &grid, int x, int y, int hook_size, int rotation) {
//     switch (rotation) {
//         case 0:
//             for (int i = 0; i < hook_size; i++) {
//                 grid.values[y+i][x] = 0;
//                 grid.values[y][x+i] = 0;
//             }
//             break;
//         case 1:
//             for (int i = 0; i < hook_size; i++) {
//                 grid.values[y+i][x] = 0;
//                 grid.values[y+hook_size-1][x+i] = 0;
//             }
//             break;
//         case 2:
//             for (int i = 0; i < hook_size; i++) {
//                 grid.values[y][x+i] = 0;
//                 grid.values[y+i][x+hook_size-1] = 0;
//             }
//             break;
//         case 3:
//             for (int i = 0; i < hook_size; i++) {
//                 grid.values[y+hook_size-1][x+i] = 0;
//                 grid.values[y+i][x+hook_size-1] = 0;
//             }
//             break;
//     }
// }
//
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
//
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

    // u64 bitmask = (1ull << 0) |
    //     (1ull << 9) |
    //     (1ull << 18) |
    //     (1ull << 27) |
    //     (1ull << 36) |
    //     (1ull << 37) |
    //     (1ull << 38) |
    //     (1ull << 39) |
    //     (1ull << 40);

    u64 bitmask = 1ull;

    set_bits(grid, bitmask, 5, 64);
    // set_hook(grid, 0, 0, 5, 0);
    print_grid(grid, 1);
    cout << endl;
    cout << grid.values[0] << endl;
    cout << endl;

    // auto end = chrono::steady_clock::now();
    // chrono::duration<double> duration = end - start;
    // cout << endl;
    // cout << "Total Combinations: " << combos << endl;
    // cout << "Execution time: " << round(duration.count() * 100) / 100 << "s" << endl;
}
