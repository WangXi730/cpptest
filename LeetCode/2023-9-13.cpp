#include"LeetCodeTools.hpp"
using namespace std;
class Solution {
public:
    bool checkValidGrid(vector<vector<int>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        int row = 0;
        int col = 0;
        for (int i = 0; i < n * m; ++i) {
            //Âí×ßÈÕ
            if (row + 2 < n && col + 1 < m && grid[row + 2][col + 1] == 1 + i) {
                row = row + 2;
                col = col + 1;
                ++i;
            }
            else if (row + 2 < n && col - 1 >= 0 && grid[row + 2][col - 1] == 1 + i) {
                row = row + 2;
                col = col - 1;
                ++i;
            }
            else if (row - 2 >= 0 && col + 1 < m && grid[row - 2][col + 1] == 1 + i) {
                row = row - 2;
                col = col + 1;
                ++i;
            }
            else if (row - 2 >= 0 && col - 1 >= 0 && grid[row - 2][col - 1] == 1 + i) {
                row = row - 2;
                col = col - 1;
                ++i;
            }
            else if (row + 1 < n && col + 2 < m && grid[row + 1][col + 2] == 1 + i) {
                row = row + 1;
                col = col + 2;
                ++i;
            }
            else if (row + 1 < n && col - 2 >= 0 && grid[row + 1][col - 2] == 1 + i) {
                row = row + 1;
                col = col - 2;
                ++i;
            }
            else if (row - 1 >= 0 && col + 2 < m && grid[row - 1][col + 2] == 1 + i) {
                row = row - 1;
                col = col + 2;
                ++i;
            }
            else if (row - 1 >= 0 && col - 2 >= 0 && grid[row - 1][col - 2] == 1 + i) {
                row = row - 1;
                col = col - 2;
                ++i;
            }
            else {
                return false;
            }
        }
        return true;
    }
};



int main() {
    vector<vector<int>> v{{0, 11, 16, 5, 20}, { 17,4,19,10,15 }, { 12,1,8,21,6 }, { 3,18,23,14,9 }, { 24,13,2,7,22 }};
    Solution test;
    test.checkValidGrid(v);
    return 0;
}