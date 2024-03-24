#include <iostream>
#include <vector>
#include <utility>
#include <unordered_set>
#include <unordered_map>

using namespace std;

const int n = 5;
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
    {0, 3},
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

pair<vector<vector<int>>, bool> valid_values(vector<vector<int>> &perms) {
    // map for counting values
    unordered_map<int, int> counts;
    // init vector to map out values
    vector<vector<int>> values(n, vector<int>(4));

    for (int i = 0; i < perms.size(); i++)
        for (int direction = 0; direction < 4; direction++) {
            // count the value
            counts[perms[i][direction]]++;

            if (perms[i][direction] != 0) {
                values[positions[i].first + direction_offsets[i].first]
                      [positions[i].second + direction_offsets[i].second] = perms[i][direction];
            }
        }
    for (auto pair : counts)
        if (pair.second > pair.first && pair.first != 0)
            return make_pair(values, false);

    return make_pair(values, true);
}

// pair<vector<vector<int>>, bool> valid_hooks(vector<vector<int>> &values) {
//
// }

bool valid(vector<vector<int>> &perms) {
    auto values_res = valid_values(perms);
    if (!values_res.second) {
        cout << "Invalid values:";
        for (auto row : values_res.first) {
            for (auto x : row) {
                cout << x << " ";
            }
            cout << endl;
        }
        print(values_res.first);
        return false;
    }
    // auto hooks_res = valid_hooks(values_res.first);
    // if (!hooks_res.second)
    //     return false;

    return true;
}

// how to check for validity of state
//   1. check for correct number of values (e.g 3x3's, 4x4's)
//   2. check for hook shape and homogenous values within hooks
//   3. check for no unfilled 2x2 regions
//   4. check for connectedness

void dfs(int node) {
    if (node == nodes.size()) {
        
    }
}

int main() {
    unsigned long long int count = 1;
    vector<vector<int>> perms;
    for (auto node : nodes) {
        auto res = get_perms(node.first, node.second);
        perms.push_back(res[0]);
        // cout << node.first << ": " << res.size() << endl;
        // count *= res.size();
    }

    for (auto perm : perms) {
        for (int val : perm)
            cout << val;
        cout << endl;
    }

    cout << "valid:" << endl;
    cout << valid(perms) << endl;
}
