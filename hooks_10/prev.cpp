#include <iostream>
#include <utility>
#include <string>
#include <chrono>
#include <cmath>
#include <cstdint>
using namespace std;
using u64 = unsigned long long int;

// ofstream cout("hooks.out");
int combos = 0;
auto start = chrono::steady_clock::now();

const int n = 9;
struct grid {
    int values[n][n];
};
using state = grid[9];

void init_grid(grid &grid) {
    for (auto &row : grid.values) {
        fill(row, row + n, 0);
    }
}
void print_grid(grid &grid) {
    cout << endl;
    for (auto &row : grid.values) {
        cout << "  ";
        for (auto &val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void set_hook(grid &grid, int x, int y, int hook_size, int rotation) {
    switch (rotation) {
        case 0:
            for (int i = 0; i < hook_size; i++) {
                grid.values[y+i][x] = hook_size;
                grid.values[y][x+i] = hook_size;
            }
            break;
        case 1:
            for (int i = 0; i < hook_size; i++) {
                grid.values[y+i][x] = hook_size;
                grid.values[y+hook_size-1][x+i] = hook_size;
            }
            break;
        case 2:
            for (int i = 0; i < hook_size; i++) {
                grid.values[y][x+i] = hook_size;
                grid.values[y+i][x+hook_size-1] = hook_size;
            }
            break;
        case 3:
            for (int i = 0; i < hook_size; i++) {
                grid.values[y+hook_size-1][x+i] = hook_size;
                grid.values[y+i][x+hook_size-1] = hook_size;
            }
            break;
    }
}

void unset_hook(grid &grid, int x, int y, int hook_size, int rotation) {
    switch (rotation) {
        case 0:
            for (int i = 0; i < hook_size; i++) {
                grid.values[y+i][x] = 0;
                grid.values[y][x+i] = 0;
            }
            break;
        case 1:
            for (int i = 0; i < hook_size; i++) {
                grid.values[y+i][x] = 0;
                grid.values[y+hook_size-1][x+i] = 0;
            }
            break;
        case 2:
            for (int i = 0; i < hook_size; i++) {
                grid.values[y][x+i] = 0;
                grid.values[y+i][x+hook_size-1] = 0;
            }
            break;
        case 3:
            for (int i = 0; i < hook_size; i++) {
                grid.values[y+hook_size-1][x+i] = 0;
                grid.values[y+i][x+hook_size-1] = 0;
            }
            break;
    }
}

bool valid(state &s, int x, int y, int hook_size, int rotation) {
    if (x + hook_size > n || y + hook_size > n)
        return false;

    switch (rotation) {
        case 0:
            for (int i = 0; i < hook_size; i++) {
                for (auto grid : s)
                    if (grid.values[y+i][x] > 0 || grid.values[y][x+i] > 0) return false;
            }
            break;
        case 1:
            for (int i = 0; i < hook_size; i++) {
                for (auto grid : s)
                    if (grid.values[y+i][x] > 0 || grid.values[y+hook_size-1][x+i] > 0) return false;
            }
            break;
        case 2:
            for (int i = 0; i < hook_size; i++) {
                for (auto grid : s)
                    if (grid.values[y][x+i] > 0 || grid.values[y+i][x+hook_size-1] > 0) return false;
            }
            break;
        case 3:
            for (int i = 0; i < hook_size; i++) {
                for (auto grid : s)
                    if (grid.values[y+i][x+hook_size-1] > 0 || grid.values[y+hook_size-1][x+i] > 0) return false;
            }
            break;
    }

    return true;
}

void dfs(state &s, int h) {
    if (h == 0) {
        combos++;
        return;
    }

    for (int x = 0; x < n - h + 1; x++) {
        for (int y = 0; y < n - h + 1; y++) {
            for (int r = 0; r < 4; r++) {
                cout << valid(s, x, y, h, r) << endl;
                if (valid(s, x, y, h, r)) {
                    set_hook(s[h-1], x, y, h, r);

                    dfs(s, h - 1);        

                    unset_hook(s[h-1], x, y, h, r);
                }

                if (h == 1)
                    break;
            }
        }
    }
}

int main() {
    state s;
    for (int i = 0; i < n; i++) {
        init_grid(s[i]);
    }

    dfs(s, n);

    auto end = chrono::steady_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Total Combinations: " << combos << endl;
    cout << "Execution time: " << round(duration.count() * 100) / 100 << "s" << endl;
}
