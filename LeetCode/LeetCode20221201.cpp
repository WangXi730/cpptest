#include<iostream>
//Definition for a binary tree node.
 struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode* res = nullptr;
        fun(root, p, q, res);
        return res;
    }
private:
    int fun(TreeNode* root, TreeNode* p, TreeNode* q, TreeNode*& res) {
        if (root == nullptr) {
            return 0;
        }
        int result = root == p || root == q ? 1 : 0;
        result += fun(root->left, p, q, res);
        result += fun(root->right, p, q, res);
        if (result == 2 && res == nullptr) {
            res = root;
        }
        return result;
    }
};

int main() {
    Solution test;
    TreeNode* root = new TreeNode(6);
    root->left = new TreeNode(2);
    root->right = new TreeNode(8);
    root->left->left = new TreeNode(0);
    root->left->right = new TreeNode(4);
    root->left->right->left = new TreeNode(3);
    root->left->right->right = new TreeNode(5);
    root->right->left = new TreeNode(7);
    root->right->right = new TreeNode(9);
    test.lowestCommonAncestor(root,root->left,root->left->right);

    return 0;
}