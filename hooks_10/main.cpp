#include <iostream>
using namespace std;

const int n = 9;
struct grid {
    int values[n][n];
};

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

bool valid(grid &grid, int x, int y, int hook_size, int rotation) {
    if (x + hook_size > n || y + hook_size > n)
        return false;

    switch (rotation) {
        case 0:
            for (int i = 0; i < hook_size; i++) {
                if (grid.values[y+i][x] > 0 || grid.values[y][x+i] > 0) return false;
            }
            break;
        case 1:
            for (int i = 0; i < hook_size; i++) {
                if (grid.values[y+i][x] > 0 || grid.values[y+hook_size-1][x+i] > 0) return false;
            }
            break;
        case 2:
            for (int i = 0; i < hook_size; i++) {
                if (grid.values[y][x+i] > 0 || grid.values[y+i][x+hook_size-1] > 0) return false;
            }
            break;
        case 3:
            for (int i = 0; i < hook_size; i++) {
                if (grid.values[y+i][x+hook_size-1] > 0 || grid.values[y+hook_size-1][x+i] > 0) return false;
            }
            break;
    }

    return true;
}

void dfs(grid &grid, int current_hook) {
    if (current_hook == 0) {
        print_grid(grid);
        return;
    }

    for (int x = 0; x < n - current_hook + 1; x++) {
        for (int y = 0; y < n - current_hook + 1; y++) {
            for (int r = 0; r < 4; r++) {
                if (valid(grid, x, y, current_hook, r)) {
                    set_hook(grid, x, y, current_hook, r);

                    dfs(grid, current_hook - 1);        

                    unset_hook(grid, x, y, current_hook, r);
                }
            }
        }
    }
}

int main() {
    grid grid;
    init_grid(grid);

    dfs(grid, n);

    return 0;
}
