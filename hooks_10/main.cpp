#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <utility>
#include <unordered_set>
#include <unordered_map>

using namespace std;

const int n = 5;
int c = 0;
ofstream outfile;
// vector<pair<int, int>> nodes = {
//     {5, 4},
//     {7, 3},
//     {9, 4},
//     {9, 4},
//     {11, 4},
//     {12, 4},
//     {14, 4},
//     {15, 3},
//     {18, 3},
//     {19, 4},
//     {22, 3},
//     {22, 4},
//     {22, 4},
//     {31, 4},
// };
//
// KEY:
// node[0] -> sum of adjacent values
// node[1] -> 
//      0: middle
//      1: on top edge
//      2: on right edge
//      3: on bottom edge
//      4: on left edge
//      5: top left corner
//      6: top right corner
//      7: bottom right corner
//      8: bottom left corner
// 
//      0
//      ^
//      |
// 3 <- * -> 1
//      |
//      v
//      2
vector<pair<int, int>> nodes = {
    {0, 5},
    {8, 4},
    {9, 0},
    {7, 2},
    {15, 0},
    {12, 2},
    {10, 8},
};
const int num_nodes = nodes.size();
// non_neighbors[j] = {x, y} => x and y must be empty
unordered_map<int, vector<int>> non_neighbors = {
    {0, {}},
    {1, {0}},
    {2, {1}},
    {3, {2}},
    {4, {3}},
    {5, {0, 3}},
    {6, {0, 1}},
    {7, {1, 2}},
    {8, {2, 3}},
};
// positions corresponding to each node's index
vector<pair<int, int>> positions = {
    {0, 0},
    {0, 2},
    {2, 1},
    {4, 1},
    {2, 3},
    {4, 3},
    {0, 4},
};
// directions to offsets
unordered_map<int, pair<int, int>> direction_offsets = {
    {0, {0, -1}},
    {1, {1, 0}},
    {2, {0, 1}},
    {3, {-1, 0}},
};

void print(vector<vector<int>> &values) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << values[j][i] << " ";
        }

        cout << endl;
    }
}

void file_print(vector<vector<int>> &values) {
    outfile.open("ans.out");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            outfile << values[j][i] << " ";
        }

        outfile << endl;
    }
    outfile.close();
}

bool valid_perm(vector<int> &curr, int sum, int target, int node_type) {
    for (int neighbor_index : non_neighbors[node_type])
        if (curr[neighbor_index] != 0)
            return false;

    return target == sum;
}

void get_perms_helper(vector<vector<int>> &res, vector<int> &curr, int target, int sum,
        int node_type) {
    if (curr.size() == 4) {
        if (valid_perm(curr, sum, target, node_type))
            res.push_back(curr);
        return;
    }

    for (int i = 0; i < n + 1; ++i) {
        curr.push_back(i);
        get_perms_helper(res, curr, target, sum + i, node_type);
        curr.pop_back();
    }
}

vector<vector<int>> get_perms(int n, int node_type) {
    vector<vector<int>> res;
    vector<int> curr;
    get_perms_helper(res, curr, n, 0, node_type);
    return res;
}

vector<vector<int>> valid_values(vector<vector<int>> &perms) {
    // map for counting values
    unordered_map<int, int> counts;
    // init vector to map out values
    vector<vector<int>> values(n, vector<int>(n, -1));

    for (int i = 0; i < perms.size(); i++) {
        for (int direction = 0; direction < 4; direction++) {
            int val = perms[i][direction];

            if (val != 0) {
                // count the value
                counts[val]++;
            }

            int x = positions[i].first + direction_offsets[direction].first;
            int y = positions[i].second + direction_offsets[direction].second;

            if (x > 0 && x < n && y > 0 && y < n) {
                if (values[x][y] != -1 // if the value has been set
                        && values[x][y] != val) { // if the values are different
                    for (auto &row : values)
                        fill(row.begin(), row.end(), -1);
                    return values;
                }
                values[x][y] = val;
            }
        }
    }

    for (auto pair : counts) {
        if (pair.second != pair.first && pair.first != 0) {
            for (auto &row : values)
                fill(row.begin(), row.end(), -1);
            return values;
        }
    }

    return values;
}

bool valid_hooks(vector<vector<int>> &values) {
    // find all n hooks
    int x = 0;
    int y = 0;
    for (int h = n; h > 1; h--) {
        // check all 4 possible hook locations

        // upper left
        unordered_set<int> seen;
        seen.insert(0);
        seen.insert(values[x][y]);
        for (int j = 1; j < h; j++) {
            seen.insert(values[x+j][y]);
            seen.insert(values[x][y+j]);
        }
        if (seen.size() < 3) {
            x++;
            y++;
            continue;
        }

        // bottom left
        seen.clear();
        seen.insert(0);
        seen.insert(values[x][y+h-1]);
        for (int j = 1; j < h; j++) {
            seen.insert(values[x+j][y+h-1]);
            seen.insert(values[x][y+h-1-j]);
        }
        if (seen.size() < 3) {
            x++;
            continue;
        }

        // bottom right
        seen.clear();
        seen.insert(0);
        seen.insert(values[x+h-1][y+h-1]);
        for (int j = 1; j < h; j++) {
            seen.insert(values[x+h-1-j][y+h-1]);
            seen.insert(values[x+h-1][y+h-1-j]);
        }
        if (seen.size() < 3) {
            continue;
        }

        // top right
        seen.clear();
        seen.insert(0);
        seen.insert(values[x+h-1][y]);
        for (int j = 1; j < h; j++) {
            seen.insert(values[x+h-1-j][y]);
            seen.insert(values[x+h-1][y+j]);
        }
        if (seen.size() < 3) {
            y++;
            continue;
        }
        
        return false;
    }

    return true; 
}

int total_values(int n) {
    if (n == 1)
        return 1;

    return n + total_values(n-1);
}

bool is_not_full(vector<vector<int>> &values) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1; j++) {
            // check 2x2 region
            if (values[i][j] && values[i][j+1] && values[i+1][j] &&
                    values[i+1][j+1])
                return false;
        }
    }
    return true;
}

struct pair_hash {
    size_t operator()(const pair<int, int> &p) const {
        return p.first * 10 + p.second;
    }
};

int dfs(vector<vector<int>> &values, int x, int y, unordered_set<pair<int, int>, pair_hash> &seen) {
    if (seen.find(make_pair(x, y)) != seen.end()
            || x < 0 || y < 0 || x >= n || y >= n
            || !values[x][y])
        return 0;
    else {
        seen.insert(make_pair(x, y));
        return dfs(values, x + 1, y, seen) +
            dfs(values, x - 1, y, seen) +
            dfs(values, x, y + 1, seen) +
            dfs(values, x, y - 1, seen) + 1;
    }
}

bool is_connected(vector<vector<int>> &values) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (values[i][j]) {
                unordered_set<pair<int, int>, pair_hash> seen;
                return dfs(values, i, j, seen) == total_values(n);
            }
        }
    }

    return false;
}

bool valid_shape(vector<vector<int>> &values) {
    return is_not_full(values) && is_connected(values);
}

// how to check for validity of state
//   1. check for correct number of values (e.g 3x3's, 4x4's)
//   2. check for hook shape and homogenous values within hooks
//   3. check for no unfilled 2x2 regions
//   4. check for connectedness
bool valid(vector<vector<int>> &perms) {
    c++;
    cout << "\033[H\033[J";
    cout << c << endl;
    auto values_res = valid_values(perms);
    if (values_res[0][0] == -1) {
        return false;
    }

    if (!valid_hooks(values_res))
        return false;

    if (!valid_shape(values_res))
        return false;

    file_print(values_res);
    return true;
}


void dfs(vector<vector<vector<int>>> all_perms, vector<vector<int>> perms, int node) {
    if (node == num_nodes) {
        // for (int i = 0; i < num_nodes; i++) {
        //     cout << "Node: " << nodes[i].first << endl;
        //     for (auto j : perms[i])
        //         cout << j;
        //     cout << endl;
        // }
        valid(perms);
        return;
    }

    for (auto perm : all_perms[node]) {
        perms[node] = perm;
        dfs(all_perms, perms, node + 1);
    }
}

int main() {
    auto start = chrono::steady_clock::now();
    vector<vector<vector<int>>> all_perms;
    vector<vector<int>> curr_perms(num_nodes);
    for (auto node : nodes) {
        auto res = get_perms(node.first, node.second);
        all_perms.push_back(res);
    }
    dfs(all_perms, curr_perms, 0);
}
