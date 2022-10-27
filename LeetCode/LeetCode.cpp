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
        //��¼����t�����ַ��ĵ�ǰ��С�Ӵ���ͷ��β���±�
        int begin = -1;
        int end = -1;
        //��¼ t �ֵ�ÿ���ַ����ֵĴ���
        map<char, int> mp;
        for (int i = 0; i < t.size(); ++i) {
            ++mp[t[i]];
        }
        //ͨ��list��¼�±�
        list<int> tmp_list;
        int size = 0;
        for (int i = 0; i < s.size(); ++i) {
            //���û������ַ�����������
            if (mp.find(s[i]) == mp.end()) {
                continue;
            }
            //��¼����ַ���λ��
            tmp_list.push_back(i);
            //���е�����ַ�����һ����������Ҫע����ǣ��ַ�����������С��0
            --mp[s[i]];
            //size��¼������Ч�ַ�
            if (mp[s[i]] >= 0) {
                ++size;
            }
            //�����Ч�ַ���t�ĳ�����ȣ���ô��begin��end���е���
            while (size == t.size()) {
                if (begin == -1 || (tmp_list.back() - tmp_list.front() < end - begin)) {
                    begin = tmp_list.front();
                    end = tmp_list.back();
                }
                ++mp[s[tmp_list.front()]];
                //���ɾ����һ����Ч�ַ�����ô�Ͳ���Ҫ��size���б䶯��
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
        //�ݹ��������
        if (k == word.size()) {
            return true;
        }
        else if (board[i][j] != word[k] || trace[i][j]) {
            return false;
        }
        //������·
        trace[i][j] = true;
        if (k == word.size() - 1) {
            return true;
        }
        //Ѱ����һ��
        if (i > 0) {
            if (func(board, word, trace, i - 1, j, k + 1)) {
                //�ɹ�����
                return true;
            }
        }
        if (j > 0) {
            if (func(board, word, trace, i, j - 1, k + 1)) {
                //�ɹ�����
                return true;
            }
        }
        if (i < board.size() - 1) {
            if (func(board, word, trace, i + 1, j, k + 1)) {
                //�ɹ�����
                return true;
            }
        }
        if (j < board[0].size() - 1) {
            if (func(board, word, trace, i, j + 1, k + 1)) {
                //�ɹ�����
                return true;
            }
        }
        //ʧ�ܻ���
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