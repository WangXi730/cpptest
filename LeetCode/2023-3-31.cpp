#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
using namespace std;
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    ~TreeNode() {
        if(left!=nullptr)
        delete left;
        if(right!=nullptr)
        delete right;
    }
    
};
class Solution {
public:
    Solution(): arr(1,1) {
    }
    vector<int> diffWaysToCompute(string expression) {
        //不管怎么说，先把数字和符号提取出来才好
        vector<int> figure;
        vector<char> sig;
        for (int i = 0; i < expression.size(); ++i) {
            if (expression[i] <= '9' && expression[i] >= '0') {
                int sum = 0;
                while (expression[i] <= '9' && expression[i] >= '0') {
                    sum *= 10;
                    sum += expression[i++] - '0';
                }
                figure.push_back(sum);
                --i;
            }
            else {
                sig.push_back(expression[i]);
            }
        }

        vector<vector<vector<int>>> dp(figure.size(), vector<vector<int>>(figure.size(), vector<int>()));//dp[i][j]为从i到j的所有解
        for (int step = 0; step < figure.size(); ++step) {
            for (int l = 0; l < figure.size() - step; ++l) {
                int r = l + step;
                if (l == r) {
                    dp[l][r].emplace_back(figure[l]);
                }
                else {
                    for (int mid = l; mid < r; ++mid) {
                        for (int i = 0; i < dp[l][mid].size(); ++i) {
                            for (int j = 0; j < dp[mid + 1][r].size(); ++j) {
                                dp[l][r].emplace_back(operation(dp[l][mid][i], dp[mid + 1][r][j], sig[mid]));
                            }
                        }
                    }
                }
            }
        }
        return dp[0][figure.size() - 1];
    }
    int operation(int num1, int num2, char sig) {
        switch (sig) {
        case '+':return num1 + num2;
        case '-':return num1 - num2;
        case '*':return num1 * num2;
        case '/':return num1 / num2;
        }
        return 0;
    }
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        vector<string> res;
        string s = to_string(root->val);
        if (root->left != nullptr)
            dfs(res, s, root->left);
        if (root->right != nullptr)
            dfs(res, s, root->right);
        return res;
    }
private:
    void dfs(vector<string>& res, string& s, TreeNode* root) {
        int size = s.size();
        s += "->" + to_string(root->val);
        if (root->left == nullptr && root->right == nullptr) {
            res.push_back(s);
            s.resize(size);
            return;
        }
        if (root->left != nullptr) {
            dfs(res, s, root->left);
        }
        if (root->right != nullptr) {
            dfs(res, s, root->right);
        }
        s.resize(size);
    }
public:
    int nthUglyNumber(int n) {
        if (n > arr.size()) {
            int i = arr.size();
            arr.resize(n);
            while (i < n) {
                if (num2 <= num3 && num2 <= num5) {
                    if (arr[i - 1] < num2) {
                        arr[i++] = num2;
                    }
                    num2 = arr[++ptr2] * 2;
                }
                else if (num3 <= num2 && num3 <= num5) {
                    if (arr[i - 1] < num3) {
                        arr[i++] = num3;
                    }
                    num3 = arr[++ptr3] * 3;
                }
                else {
                    if (arr[i - 1] < num5) {
                        arr[i++] = num5;
                    }
                    num5 = arr[++ptr5] * 5;
                }
            }
        }
        return arr[n - 1];
    }
    int ptr2 = 0;
    int ptr3 = 0;
    int ptr5 = 0;
    int num2 = 2;
    int num3 = 3;
    int num5 = 5;
    vector<int> arr;
};



int main() {
    Solution test;
    test.nthUglyNumber(10);
    return 0;
}