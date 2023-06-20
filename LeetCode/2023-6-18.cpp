#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int res = 0;
        for (int i = 1; i < grid.size(); ++i) {
            for (int j = 1; j < grid[0].size(); ++j) {
                if (grid[i][j] == 0) {
                    if (dfs(grid, i, j)) {
                        ++res;
                    }
                }
            }
        }
        return res;
    }
    bool dfs(vector<vector<int>>& grid, int i, int j) {
        if (i < 0 || j < 0 || i == grid.size() || j == grid[i].size()) {
            return false;
        }
        if (grid[i][j] == 0) {
            grid[i][j] = 1;
            bool left = dfs(grid, i - 1, j);
            bool right = dfs(grid, i + 1, j);
            bool up = dfs(grid, i, j - 1);
            bool down = dfs(grid, i, j + 1);
            return up && down && right && left;
        }
        return true;
    }
};
#include"LeetCode_array.hpp"
int main() {
    Solution test;
    vector<vector<int>> grid{ {1,1,1,1,1,1,1,0},{1,0,0,0,0,1,1,0},{1,0,1,0,1,1,1,0},{1,0,0,0,0,1,0,1},{1,1,1,1,1,1,1,0} };
    test.closedIsland(grid);
    return 0;
}