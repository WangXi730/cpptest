#include<iostream>
#include<vector>
#include<string>
#include<ctime>
#include"LeetCode_array.hpp"
#include<unordered_map>
using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        vector<vector<bool>> col(9, vector<bool>(9, false));
        vector<vector<bool>> row(9, vector<bool>(9, false));
        vector<vector<bool>> block(9, vector<bool>(9, false));
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] != '.') {
                    int t = board[i][j] - '1';
                    row[i][t] = true;
                    col[j][t] = true;
                    block[i / 3 * 3 + j / 3][t] = true;
                }
            }
        }//厘1/100，分1/10
        dfs(board, row, col, block);
    }
private:
    void print(vector<vector<char>>& mat) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                cout << mat[i][j] << '\t';
            }
            cout << '\n';
        }
        cout << endl;
    }
    void print(vector<vector<bool>>& mat) {
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                cout << mat[i][j] << '\t';
            }
            cout << '\n';
        }
        cout << endl;
    }

    bool dfs(vector<vector<char>>& board, vector<vector<bool>> row, vector<vector<bool>> col, vector<vector<bool>> block) {
        //找到本次要填的空
        int i_idx = -1;
        int j_idx = -1;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    i_idx = i;
                    j_idx = j;
                    goto point;
                }
            }
        }
        point:
        //递归结束条件
        if (i_idx == -1) {
            return true;
        }
        //找到可以填的数字
        for (int i = 0; i < 9; ++i) {
            if (row[i_idx][i] || col[j_idx][i] || block[i_idx / 3 * 3 + j_idx / 3][i]) {
            }
            else {
                board[i_idx][j_idx] = i + '1';
                row[i_idx][i] = true;
                col[j_idx][i] = true;
                block[i_idx / 3 * 3 + j_idx / 3][i] = true;
                print(board);
                print(row);
                print(col);
                print(block);
                if (dfs(board, row, col, block)) {
                    return true;
                }
                row[i_idx][i] = false;
                col[j_idx][i] = false;
                block[i_idx / 3 * 3 + j_idx / 3][i] = false;
            }
        }
        //回溯
        board[i_idx][j_idx] = '.';
        return false;
    }

public:
    int longestConsecutive(vector<int>& nums) {
        if (nums.empty()) {
            return 0;
        }
        int inf = nums[0];
        int sup = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] > sup) {
                sup = nums[i];
            }
            if (nums[i] < inf) {
                inf = nums[i];
            }
        }
        unordered_map<int,int> v;
        for (int i = 0; i < nums.size(); ++i) {
            v[nums[i] - inf] = 1;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (!v[nums[i] - inf]||nums[i]==sup) {
                continue;
            }
            int j = nums[i] - inf + 1;
            while (j <= sup-inf && v[j]) {
                v[nums[i] - inf] += v[j];
                v[j++] = 0;
            }
            if (nums[i] != inf && v[nums[i] - inf - 1] != 0) {
                v[nums[i] - inf - 1] += v[nums[i] - inf];
                v[nums[i] - inf] = 0;
            }
        }
        int res = v[nums[0]-inf];
        for (int i = 1; i < nums.size(); ++i) {
            if (res < v[nums[i]-inf]) {
                res = v[nums[i]-inf];
            }
        }
        return res;
    }
};

void func(string& s) {
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '"') {
            s[i] = '\'';
        }
    }
}

int main() {
    Solution test;/*
    string s = R"( [["5", "3", ".", ".", "7", ".", ".", ".", "."], ["6", ".", ".", "1", "9", "5", ".", ".", "."], [".", "9", "8", ".", ".", ".", ".", "6", "."], ["8", ".", ".", ".", "6", ".", ".", ".", "3"], ["4", ".", ".", "8", ".", "3", ".", ".", "1"], ["7", ".", ".", ".", "2", ".", ".", ".", "6"], [".", "6", ".", ".", ".", ".", "2", "8", "."], [".", ".", ".", "4", "1", "9", ".", ".", "5"], [".", ".", ".", ".", "8", ".", ".", "7", "9"]])";
    array_to_c(s);
    func(s);
    cout << s;
    vector<vector<char>> boart{ {'5', '3', '.', '.', '7', '.', '.', '.', '.'}, {'6', '.', '.', '1', '9', '5', '.', '.', '.'}, {'.', '9', '8', '.', '.', '.', '.', '6', '.'}, {'8', '.', '.', '.', '6', '.', '.', '.', '3'}, {'4', '.', '.', '8', '.', '3', '.', '.', '1'}, {'7', '.', '.', '.', '2', '.', '.', '.', '6'}, {'.', '6', '.', '.', '.', '.', '2', '8', '.'}, {'.', '.', '.', '4', '1', '9', '.', '.', '5'}, {'.', '.', '.', '.', '8', '.', '.', '7', '9'} };
    test.solveSudoku(boart);*/
    vector<int> nums{ -8,-4,9,9,4,6,1,-4,-1,6,8 };
    int t = time(NULL);
    test.longestConsecutive(nums);
    t = time(NULL) - t;
    cout << t;
    return 0;
}