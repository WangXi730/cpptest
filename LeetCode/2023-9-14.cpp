#include"LeetCodeTools.hpp"
#include<iostream>
using namespace std;
using TreeNode = wx::TreeNode<int>;
class Solution {
public:
    vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
        vector<vector<int>> arr(8, vector<int>(8, -1));
        for (int i = 0; i < queens.size(); ++i) {
            arr[queens[i][0]][queens[i][1]] = i;
        }
        vector<vector<int>> res;
        //遍历每一个方向
        int i = king[0] - 1;
        int j = king[1] - 1;
        while (i >= 0 && j >= 0) {
            if (arr[i][j] != -1) {
                res.push_back(queens[arr[i][j]]);
                break;
            }
            --i;
            --j;
        }
        i = king[0];
        j = king[1] - 1;
        while (j >= 0) {
            if (arr[i][j] != -1) {
                res.push_back(queens[arr[i][j]]);
                break;
            }
            --j;
        }
        i = king[0] - 1;
        j = king[1];
        while (i >= 0) {
            if (arr[i][j] != -1) {
                res.push_back(queens[arr[i][j]]);
                break;
            }
            --i;
        }
        i = king[0] + 1;
        j = king[1] + 1;
        while (i < 8 && j < 8) {
            if (arr[i][j] != -1) {
                res.push_back(queens[arr[i][j]]);
                break;
            }
            ++i;
            ++j;
        }
        i = king[0];
        j = king[1] + 1;
        while (j < 8) {
            if (arr[i][j] != -1) {
                res.push_back(queens[arr[i][j]]);
                break;
            }
            ++j;
        }
        i = king[0] + 1;
        j = king[1];
        while (i < 8) {
            if (arr[i][j] != -1) {
                res.push_back(queens[arr[i][j]]);
                break;
            }
            ++i;
        }
        i = king[0] - 1;
        j = king[1] + 1;
        while (i >= 0 && j < 8) {
            if (arr[i][j] != -1) {
                res.push_back(queens[arr[i][j]]);
                break;
            }
            --i;
            ++j;
        }
        i = king[0] + 1;
        j = king[1] - 1;
        while (i < 8 && j >= 0) {
            if (arr[i][j] != -1) {
                res.push_back(queens[arr[i][j]]);
                break;
            }
            ++i;
            --j;
        }
        return res;
    }

public:
    int goodNodes(TreeNode* root) {
        int res = 1;
        int max_val = root->val;
        dfs(res, root->left, max_val);
        dfs(res, root->right, max_val);
        return res;
    }
private:
    void dfs(int& res, TreeNode* root, int max_val) {
        if (root == nullptr) {
            return;
        }
        if (max_val <= root->val) {
            ++res;
            max_val = root->val;
        }
        dfs(res, root->left, max_val);
        dfs(res, root->right, max_val);
    }
public:
    int countServers(vector<vector<int>>& grid) {
        vector<int> col(grid[0].size(), 0);
        vector<int> row(grid.size(), 0);
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j]) {
                    ++row[i];
                    ++col[j];
                }
            }
        }
        int res = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                if (grid[i][j] && (col[j] > 1 || row[i] > 1)) {
                    ++res;
                }
            }
        }
        return res;
    }
};

int main() {
    vector<vector<int>> q;
    wx::create("[[0,1],[1,0],[4,0],[0,4],[3,3],[2,4]]", q);
    vector<int> king{0, 0};
    Solution test;
    //test.queensAttacktheKing(q, king);
    TreeNode* tree;
    wx::create("[3,1,4,3,null,1,5]", tree);
    //test.goodNodes(tree);
    vector<vector<int>> grid;
    wx::create("[[1,0,0,1,0],[0,0,0,0,0],[0,0,0,1,0]]", grid);
    test.countServers(grid);
    return 0;
}