#include<iostream>
#include<list>
#include<string>
#include<vector>
#include<map>
#include"LeetCode_array.hpp"

using namespace std;

class Solution {
public:
    string minWindow(string s, string t) {
        //记录涵盖t所有字符的当前最小子串的头和尾的下标
        int begin = -1;
        int end = -1;
        //记录 t 种的每个字符出现的次数
        map<char, int> mp;
        for (int i = 0; i < t.size(); ++i) {
            ++mp[t[i]];
        }
        //通过list记录下标
        list<int> tmp_list;
        int size = 0;
        for (int i = 0; i < s.size(); ++i) {
            //如果没有这个字符，跳过即可
            if (mp.find(s[i]) == mp.end()) {
                continue;
            }
            //记录这个字符的位置
            tmp_list.push_back(i);
            //现有的这个字符减少一个，这里需要注意的是，字符的数量可以小于0
            --mp[s[i]];
            //size记录的是有效字符
            if (mp[s[i]] >= 0) {
                ++size;
            }
            //如果有效字符与t的长度相等，那么对begin和end进行迭代
            while (size == t.size()) {
                if (begin == -1 || (tmp_list.back() - tmp_list.front() < end - begin)) {
                    begin = tmp_list.front();
                    end = tmp_list.back();
                }
                ++mp[s[tmp_list.front()]];
                //如果删除了一个无效字符，那么就不需要对size进行变动了
                if (mp[s[tmp_list.front()]] > 0) {
                    --size;
                }
                tmp_list.pop_front();
            }
        }
        if (begin == -1) {
            return "";
        }
        return string(s.begin() + begin, s.begin() + end + 1);
    }
public:
    bool exist(vector<vector<char>>& board, string word) {
        vector<vector<int>> begin;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j] == word[0]) {
                    begin.push_back({i,j});
                }
            }
        }
        for (auto& b : begin) {
            vector<vector<bool>> trace(board.size(), vector<bool>(board[0].size(), false));
            if (func(board, word, trace, b[0], b[1], 0)) {
                return true;
            }
        }
        return false;
    }
private:
    bool func(vector<vector<char>>& board, string& word, vector<vector<bool>>& trace, int i, int j, int k) {
        //递归结束条件
        if (k == word.size()) {
            return true;
        }
        else if (board[i][j] != word[k] || trace[i][j]) {
            return false;
        }
        //走这条路
        trace[i][j] = true;
        if (k == word.size() - 1) {
            return true;
        }
        //寻找下一步
        if (i > 0) {
            if (func(board, word, trace, i - 1, j, k + 1)) {
                //成功返回
                return true;
            }
        }
        if (j > 0) {
            if (func(board, word, trace, i, j - 1, k + 1)) {
                //成功返回
                return true;
            }
        }
        if (i < board.size() - 1) {
            if (func(board, word, trace, i + 1, j, k + 1)) {
                //成功返回
                return true;
            }
        }
        if (j < board[0].size() - 1) {
            if (func(board, word, trace, i, j + 1, k + 1)) {
                //成功返回
                return true;
            }
        }
        //失败回溯
        trace[i][j] = false;
        return false;
    }
};


int main() {
    Solution test;
    //test.minWindow("ADOBECODEBANC", "ABC");
    vector<vector<char>> board{ {'a'} };
    test.exist(board, "a");
    return 0;
}