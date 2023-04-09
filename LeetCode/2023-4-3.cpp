#include<iostream>
#include<unordered_set>
#include<vector>
#include"LeetCode_array.hpp"

using namespace std;

void gameOfLife(vector<vector<int>>& board) {
    vector<vector<int>> res(board.size(), vector<int>(board[0].size()));
    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[0].size(); ++j) {
            if (board[i][j] == 0) {
                continue;
            }
            if (i > 0) {
                if (j > 0) {
                    res[i - 1][j - 1] += 1;
                }
                if (j + 1 < res[0].size()) {
                    res[i - 1][j + 1] += 1;
                }
                res[i - 1][j] += 1;
            }
            if (i + 1 < res.size()) {
                if (j > 0) {
                    res[i + 1][j - 1] += 1;
                }
                if (j + 1 < res[0].size()) {
                    res[i + 1][j + 1] += 1;
                }
                res[i + 1][j] += 1;
            }
            if (j > 0) {
                res[i][j - 1] += 1;
            }
            if (j + 1 < res[0].size()) {
                res[i][j + 1] += 1;
            }
        }
    }
    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[0].size(); ++j) {
            switch (res[i][j]) {
            case 2: res[i][j] = board[i][j]; break;
            case 3: res[i][j] = 1; break;
            default: res[i][j] = 0; break;
            }
        }
    }
    res.swap(board);
}
class Solution {
public:
    bool wordPattern(string pattern, string s) {
        string sumap[26];
        unordered_set<string> uset;
        vector<string> words = split(s, ' ');
        if (pattern.size() != words.size()) {
            return false;
        }
        for (int i = 0; i < words.size(); ++i) {
            if (sumap[pattern[i] - 'a'] == "") {
                if (uset.find(words[i]) != uset.end()) {
                    return false;
                }
                sumap[pattern[i] - 'a'] = words[i];
                uset.insert(words[i]);
            }
            else {
                if (sumap[pattern[i] - 'a'] != words[i]) {
                    return false;
                }
            }
        }
        return true;
    }
    static vector<string> split(string& s, char c) {
        int begin = 0;
        vector<string> res;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == c) {
                res.push_back(s.substr(begin, i - begin));
                begin = i + 1;
            }
        }
        res.push_back(s.substr(begin));
        return res;
    }
};

class MedianFinder {
public:
    MedianFinder() {

    }


    ~MedianFinder() {
        if (left_begin == right_begin) {
            right_begin = left_begin->right;
        }
        while (left_begin != nullptr) {
            ListNode* tmp = left_begin;
            left_begin = left_begin->left;
            delete tmp;
        }
        while (right_begin != nullptr) {
            ListNode* tmp = right_begin;
            right_begin = right_begin->right;
            delete tmp;
        }
    }
    void addNum(int num) {
        if (left_begin == nullptr && right_begin == nullptr) {
            left_begin = new ListNode(num);
            right_begin = left_begin;
            left_last = right_last = left_begin;
        }
        else if (num <= left_last->val) {
            ListNode* tmp = new ListNode(num);
            tmp->right = left_last;
            left_last->left = tmp;
            left_last = tmp;
            if (left_begin == right_begin) {
                left_begin = left_begin->left;
            }
            else {
                right_begin = left_begin;
            }
        }
        else if (num >= right_last->val) {
            ListNode* tmp = new ListNode(num);
            tmp->left = right_last;
            right_last->right = tmp;
            right_last = tmp;
            if (left_begin == right_begin) {
                right_begin = right_begin->right;
            }
            else {
                left_begin = right_begin;
            }
        }
        else if (left_begin != right_begin) {
            if (num <= right_begin->val) {
                if (num > left_begin->val || num == left_begin->val || num == right_begin->val) {
                    left_begin->right = new ListNode(num);
                    left_begin->right->left = left_begin;
                    if (left_begin->right != nullptr)
                        left_begin->right->right = right_begin;
                    left_begin = left_begin->right;
                    right_begin->left = left_begin;
                }
                else {
                    ListNode* node = left_begin;
                    while (num < node->val) {
                        node = node->left;
                    }
                    ListNode* node_right = node->right;
                    node->right = new ListNode(num);
                    node->right->left = node;
                    node = node->right;
                    node->right = node_right;
                    node_right->left = node;
                }
                right_begin = left_begin;
            }
            else {
                ListNode* node = right_begin;
                while (num > node->val) {
                    node = node->right;
                }
                ListNode* node_left = node->left;
                node->left = new ListNode(num);
                node->left->right = node;
                node = node->left;
                node->left = node_left;
                node_left->right = node;
                left_begin = right_begin;
            }
        }
        else {
            if (num == right_begin->val) {
                left_begin = new ListNode(num);
                left_begin->left = right_begin->left;
                if (left_begin->left != nullptr)
                    left_begin->left->right = left_begin;
                left_begin->right = right_begin;
                right_begin->left = left_begin;
            }
            else if (num < right_begin->val) {
                ListNode* node = left_begin;
                while (num < node->val) {
                    node = node->left;
                }
                ListNode* node_right = node->right;
                node->right = new ListNode(num);
                node->right->left = node;
                node = node->right;
                node->right = node_right;
                node_right->left = node;
                left_begin = right_begin->left;
            }
            else {
                ListNode* node = right_begin;
                while (node != nullptr && num > node->val) {
                    node = node->right;
                }
                ListNode* node_left = node->left;
                node->left = new ListNode(num);
                node->left->right = node;
                node = node->left;
                node->left = node_left;
                node_left->right = node;
                right_begin = left_begin->right;
            }
        }
    }

    double findMedian() {
        return ((double)(left_begin->val + right_begin->val)) / 2;
    }
    //底层用双链表实现
    struct ListNode {
        ListNode(int data) {
            val = data;
        }
        ListNode* left = nullptr;
        ListNode* right = nullptr;
        int val;
    };
    ListNode* left_begin = nullptr;
    ListNode* right_begin = nullptr;
    ListNode* left_last = nullptr;
    ListNode* right_last = nullptr;
};



int main() {
    MedianFinder m;
    m.addNum(0);
    m.addNum(0);
    cout << m.findMedian();
    
    return 0;
}