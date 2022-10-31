#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>

using namespace std;

// Definition for a binary tree node.
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
     vector<TreeNode*> generateTrees(int n) {
         return _generateTrees(0, n + 1);
     }
 private:
     vector<TreeNode*> _generateTrees(int inf, int sup) {
         if (inf >= sup) {
             return {};
         }
         vector<TreeNode*> res;
         //选择这次的结点
         for (int i = inf + 1; i < sup; ++i) {
             //获取下一层
             vector<TreeNode*> l = _generateTrees(inf, i);
             vector<TreeNode*> r = _generateTrees(i, sup);
             if (l.size() == 0) {
                 if (r.size() == 0) {
                     res.push_back(new TreeNode(i));
                     continue;
                 }
                 for (int k = 0; k < r.size(); ++k) {
                     res.push_back(new TreeNode(i));
                     res[res.size() - 1]->right = r[k];
                 }
             }
             if (r.size() == 0) {
                 for (int j = 0; j < l.size(); ++j) {
                     res.push_back(new TreeNode(i));
                     res[res.size() - 1]->left = l[j];
                 }
             }
             for (int j = 0; j < l.size(); ++j) {
                 for (int k = 0; k < r.size(); ++k) {
                     res.push_back(new TreeNode(i));
                     res[res.size() - 1]->left = l[j];
                     res[res.size() - 1]->right = r[k];
                 }
             }
         }
         return res;
     }
 public:
     int numTrees(int n) {
         return _numTrees(0, n + 1);
     }
 private:
     int _numTrees(int inf, int sup) {
         //递归结束条件
         if (inf >= sup - 1) {
             return 0;
         }
         // i 为当前节点
         int res = 0;
         for (int i = inf + 1; i < sup; ++i) {
             int l = _numTrees(inf, i);
             int r = _numTrees(i, sup);
             if (l == 0) {
                 if (r == 0) {
                     res += 1;
                     continue;
                 }
                 res += r;
                 continue;
             }
             if (r == 0) {
                 res += l;
                 continue;
             }
             res += (l * r);
         }
         return res;
     }
 };

int main() {
    Solution test;
    //test.generateTrees(3);
    cout << test.numTrees(3);
    return 0;
}