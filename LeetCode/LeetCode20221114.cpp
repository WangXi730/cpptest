#include<iostream>
#include<vector>
#include<map>
#include<stack>
#include<string>
#include"LeetCode_array.hpp"
using namespace std;

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.size() <= 2) {
            return;
        }
        else if (board[0].size() <= 2) {
            return;
        }
        for (int i = 0; i < board.size(); i++) {
            _dfs(board, i, 0);
            _dfs(board, i, board[0].size() - 1);
        }
        for (int j = 0; j < board[0].size(); j++) {
            _dfs(board, 0, j);
            _dfs(board, board.size() - 1, j);
        }
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j] == '-') {
                    board[i][j] = 'O';
                }
                else if (board[i][j] == 'O') {
                    board[i][j] = 'X';
                }
            }
        }
    }
private:
    void _dfs(vector<vector<char>>& board, int i, int j) {
        if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size() || board[i][j] != 'O') {
            return;
        }
        board[i][j] = '-';
        _dfs(board, i - 1, j);
        _dfs(board, i + 1, j);
        _dfs(board, i, j - 1);
        _dfs(board, i, j + 1);
    }
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        if (gas.size() == 1) {
            return gas[0] >= cost[0] ? 0 : -1;
        }
        int i = 0;
        int n = gas.size();
        vector<int> v(n, 0);
        for (int j = 0; j < n; ++j) {
            v[j] = gas[j] - cost[j];
        }
        int j = i + 1;
        int sum = v[i];
        while (j != i) {
            while (sum < 0) {
                sum -= v[i];
                ++i;
                if (i >= n) {
                    return -1;
                }
            }
            sum += v[j];
            ++j;
            j %= n;
        }
        if (sum < 0) {
            return -1;
        }
        return i;
    }
};
int main() {
    Solution test;
    //string s = R"([["O","X","X","X","X","X","O","O"],["O","O","O","X","X","X","X","O"],["X","X","X","X","O","O","O","O"],["X","X","X","X","X","X","X","X"],["O","X","X","X","X","X","O","O"],["O","X","X","X","X","X","X","O"],["O","X","X","X","X","X","O","O"],["O","X","X","X","X","O","X","X"]])";
    //array_to_c(s);
    //for (int i = 0; i < s.size(); ++i) {
    //    if (s[i] == '\"') {
    //        s[i] = '\'';
    //    }
    //}
    ////cout << s;
    //vector<vector<char>> v{ {'O','X','X','X','X','X','O','O'},{'O','O','O','X','X','X','X','O'},{'X','X','X','X','O','O','O','O'},{'X','O','X','O','O','X','X','X'},{'O','X','O','X','X','X','O','O'},{'O','X','X','O','O','X','X','O'},{'O','X','O','X','X','X','O','O'},{'O','X','X','X','X','O','X','X'} };
    //for (int i = 0; i < v.size(); ++i) {
    //    for (int j = 0; j < v[0].size(); ++j) {
    //        cout << v[i][j] << "\t";
    //    }
    //    cout << "\n";
    //}
    //cout << endl;
    //vector<vector<char>> v2{ {'O','X','X','X','X','X','O','O'},{'O','O','O','X','X','X','X','O'},{'X','X','X','X','O','O','O','O'},{'X','X','X','X','X','X','X','X'},{'O','X','X','X','X','X','O','O'},{'O','X','X','X','X','X','X','O'},{'O','X','X','X','X','X','O','O'},{'O','X','X','X','X','O','X','X'} };
    //for (int i = 0; i < v.size(); ++i) {
    //    for (int j = 0; j < v[0].size(); ++j) {
    //        cout << v2[i][j] << "\t";
    //    }
    //    cout << "\n";
    //}
    ////test.solve(v);
    vector<int> v1{ 2, 3, 4 };
    vector<int> v2{ 3, 4, 3 };
    test.canCompleteCircuit(v1,v2);
    return 0;
}