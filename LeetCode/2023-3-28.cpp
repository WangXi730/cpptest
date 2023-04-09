#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
 //Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
 

class Solution {
public:
    int countNodes(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        else if (root->left == nullptr && root->right == nullptr) {
            return 1;
        }
        int res = -1;
        TreeNode* end = nullptr;
        dfs(0, root, res, end);
        if (end != nullptr) {
            if (end->left == nullptr) {
                return res * 2 + 1;
            }
        }
        return res * 2 + 2;
    }
    int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        //先计算两个矩阵各自的面积，减去重合的面积即可
        int s1 = (ax1 - ax2) * (ay1 - ay2);
        if (s1 < 0) {
            s1 = -s1;
        }
        int s2 = (bx1 - bx2) * (by1 - by2);
        if (s2 < 0) {
            s2 = -s2;
        }
        int s = s1 + s2;
        vector<pair<int, char>> vx{ {ax1,'a'},{ax2,'a'},{bx1,'b'},{bx2,'b'} };
        vector<pair<int, char>> vy{ {ay1,'a'},{ay2,'a'},{by1,'b'},{by2,'b'} };
        sort(vx.begin(), vx.end(), func);
        sort(vy.begin(), vy.end(), func);
        if (vx[0].second == vx[1].second || vy[0].second == vy[1].second) {
            return s;
        }
        int s3 = (vx[2].first - vx[1].first) * (vy[2].first - vy[1].first);
        if (s3 < 0) {
            s3 = -s3;
        }
        s -= s3;
        return s;
    }
    static bool func(pair<int, char>& a, pair<int, char>& b) {
        return a.first < b.first;
    }
    int calculate(string s) {
        int parenthesis_stack = 0;
        int res = 0;
        int sig = 1;
        int i = 0;
        while (i < s.size()) {
            if (s[i] == '+') {
                sig = 1;
            }
            else if (s[i] == '-') {
                sig = -1;
            }
            else if (s[i] <= '9' && s[i] >= '0') {
                int num = 0;
                while (s[i] <= '9' && s[i] >= '0') {
                    num *= 10;
                    num += s[i] - '0';
                    ++i;
                }
                res += num * sig;
                --i;
            }
            else if (s[i] == '(') {
                parenthesis_stack += 1;
                int j = i;
                while (parenthesis_stack != 0) {
                    ++j;
                    if (s[j] == '(') {
                        ++parenthesis_stack;
                    }
                    else if (s[j] == ')') {
                        --parenthesis_stack;
                    }
                }
                //递归
                res += sig * calculate(s.substr(i + 1, j - (i + 1)));
                i = j;
            }
            ++i;
        }
        return res;
    }
private:
    void dfs(int Node_idx, TreeNode* root, int& res, TreeNode*& end) {
        //递归结束条件
        if (root->left == nullptr || root->right == nullptr) {
            if (res == -1 || res > Node_idx) {
                end = root;
                res = Node_idx;
            }
            //剪枝
            return;
        }
        dfs(Node_idx * 2 + 1, root->left, res, end);
        dfs(Node_idx * 2 + 2, root->right, res, end);
    }
};


int main() {

    Solution test;
    std::cout <<  test.calculate("(1+(4+5+2)-3)+(6+8)");
    return 0;
}