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
 public:
     bool isInterleave(string s1, string s2, string s3) {
         if (s1.size() + s2.size() != s3.size()) {
             return false;
         }
         //dp[i][j]表示，s1的前i个字符与s2的前j个字符是否能交错s3的前i+j个字符
         vector<vector<bool>> dp(s1.size() + 1, vector<bool>(s2.size() + 1, false));
         //1、构造状态转移方程：dp[i][j]成立，如果dp[i][j-1]成立且s2[j-1]==s3[i+j-1]，或者dp[i-1][j]成立且s1[i-1]==s3[i+j-1];
         //2、初始化dp，由状态转移方程可知，dp[i][j]与dp[i-1][j]和dp[i][j-1]有关，所以初始化第0行和第0列
         dp[0][0] = true;
         for (int i = 1; i <= s1.size(); ++i) {
             dp[i][0] = dp[i - 1][0] && s1[i-1] == s3[i-1];
         }
         for (int j = 1; j <= s2.size(); ++j) {
             dp[0][j] = dp[0][j - 1] && s2[j-1] == s3[j-1];
         }
         //3、开始创建dp
         for (int i = 1; i <= s1.size(); ++i) {
             for (int j = 1; j <= s2.size(); ++j) {
                 dp[i][j] = (dp[i - 1][j] && s1[i - 1] == s3[i + j - 1]) || (dp[i][j - 1] && s2[j - 1] == s3[i + j - 1]);
             }
         }
         //打印dp数组
         for (int i = 0; i <= s1.size(); ++i) {
             for (int j = 0; j <= s2.size(); ++j) {
                 if (dp[i][j]) {
                     cout << "true" << "\t";
                 }
                 else{
                     cout << "false" << "\t";
                 }
             }
             cout << "\n";
         }
         return dp[s1.size()][s2.size()];
     }
 };

int main() {
    Solution test;
    //test.generateTrees(3);
    //cout << test.numTrees(3);
    test.isInterleave("",
"b",
"b");
    return 0;
}