#include"LeetCodeTools.hpp"
using namespace std;
class Solution {
public:
    bool checkValidGrid(vector<vector<int>>& grid) {
        if (grid[0][0] != 0) {
            return false;
        }
        int n = grid.size();
        int m = grid[0].size();
        int row = 0;
        int col = 0;
        for (int i = 0; i < n * m - 1; ++i) {
            //Âí×ßÈÕ
            if (row + 2 < n && col + 1 < m && grid[row + 2][col + 1] == 1 + i) {
                row = row + 2;
                col = col + 1;
            }
            else if (row + 2 < n && col - 1 >= 0 && grid[row + 2][col - 1] == 1 + i) {
                row = row + 2;
                col = col - 1;
            }
            else if (row - 2 >= 0 && col + 1 < m && grid[row - 2][col + 1] == 1 + i) {
                row = row - 2;
                col = col + 1;
            }
            else if (row - 2 >= 0 && col - 1 >= 0 && grid[row - 2][col - 1] == 1 + i) {
                row = row - 2;
                col = col - 1;
            }
            else if (row + 1 < n && col + 2 < m && grid[row + 1][col + 2] == 1 + i) {
                row = row + 1;
                col = col + 2;
            }
            else if (row + 1 < n && col - 2 >= 0 && grid[row + 1][col - 2] == 1 + i) {
                row = row + 1;
                col = col - 2;
            }
            else if (row - 1 >= 0 && col + 2 < m && grid[row - 1][col + 2] == 1 + i) {
                row = row - 1;
                col = col + 2;
            }
            else if (row - 1 >= 0 && col - 2 >= 0 && grid[row - 1][col - 2] == 1 + i) {
                row = row - 1;
                col = col - 2;
            }
            else {
                return false;
            }
        }
        return true;
    }
    int numFactoredBinaryTrees(vector<int>& arr) {
        sort(arr.begin(), arr.end());
        unordered_map<int, int> mp;
        int res = 0;
        for (int i = 0; i < arr.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (arr[i] % arr[j] != 0) {
                    continue;
                }
                int t = arr[i] / arr[j];
                if (mp.find(t) != mp.end()) {
                    mp[arr[i]] += mp[t] * mp[arr[j]];
                }
            }
            mp[arr[i]] += 1;
            res += mp[arr[i]];
        }
        return res;
    }
};


int main() {
    //vector<vector<int>> v{{8, 3, 6}, { 5,0,1 }, { 2,7,4 }};
    //Solution test;
    //cout << boolalpha << test.checkValidGrid(v);
    vector<int> v = wx::create_vector_int("[2,4,5,10]");
    Solution test;
    cout << test.numFactoredBinaryTrees(v);
    return 0;
}