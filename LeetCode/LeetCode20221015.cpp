#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        helper(res, {}, 0, 0, target, candidates);
        return res;
    }
private:
    void helper(vector<vector<int>>& res, vector<int> tmp, int i, int sum, int target, vector<int>& candidates) {
        if (sum > target) {
            return;
        }
        else if (sum == target) {
            res.push_back(tmp);
            return;
        }
        helper(res, tmp, i + 1, sum, target, candidates);
        tmp.push_back(candidates[i]);
        sum += candidates[i];
        helper(res, tmp, i, sum, target, candidates);
    }
public:
    void setZeroes(vector<vector<int>>& matrix) {
        //标记要置为0的行列
        unordered_set<int> row;
        unordered_set<int> col;
        int m = matrix.size();
        int n = matrix[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    row.insert(i);
                    col.insert(j);
                }
            }
        }
        //开始置0
        //行
        for (auto& i : row) {
            matrix[i] = vector<int>(n, 0);
        }
        //列
        for (auto& i : col) {
            for (int j = 0; j < m; ++j) {
                matrix[j][i] = 0;
            }
        }
    }
    bool isFlipedString(string s1, string s2) {
        if (s1.size() != s2.size()) {
            return false;
        }
        s1 += s1;
        int pos = s1.find(s2);
        if (pos == -1) {
            return false;
        }
        return true;
    }
};


int main() {
    Solution test;
    test.isFlipedString("waterbottle", "erbottlewat");
    return 0;
}