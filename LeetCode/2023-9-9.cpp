
#include<iostream>
#include<vector>
#include<map>
#include<algorithm>
#include"LeetCode_array.hpp"
using namespace std;

using TreeNode = wx::TreeNode_int;
class Solution {
public:
    TreeNode* lcaDeepestLeaves(TreeNode* root) {
        if (root == nullptr ||( root->left == nullptr && root->right == nullptr)) {
            return root;
        }
        TreeNode* res = nullptr;
        pair<TreeNode*, int>* leaf1 = nullptr;
        pair<TreeNode*, int>* leaf2 = nullptr;
        dfs(root, &leaf2, &leaf2, &res, 0);
        if (leaf1 != nullptr) {
            delete leaf1;
        }
        if (leaf2 != nullptr) {
            delete leaf2;
        }
        return res;
    }
private:
    void dfs(TreeNode* root, pair<TreeNode*, int>** leaf1, pair<TreeNode*, int>** leaf2, TreeNode** res, int deep) {
        if (root->left == nullptr && root->right == nullptr) {
            *leaf1 = new pair<TreeNode*, int>(root, deep); //make_pair(root, deep);
            return;
        }
        pair<TreeNode*, int>* leaf11 = nullptr;
        pair<TreeNode*, int>* leaf12 = nullptr;
        pair<TreeNode*, int>* leaf21 = nullptr;
        pair<TreeNode*, int>* leaf22 = nullptr;
        TreeNode* res1 = nullptr;
        TreeNode* res2 = nullptr;
        if (root->left != nullptr) {
            dfs(root->left, &leaf11, &leaf12, &res1, deep + 1);
        }
        if (root->right != nullptr) {
            dfs(root->right, &leaf21, &leaf22, &res2, deep + 1);
        }


        if (res1 != nullptr && res2 == nullptr) {
            *leaf1 = leaf11;
            *leaf2 = leaf12;
            *res = res1;
        }
        else if (res1 == nullptr && res2 != nullptr) {
            *leaf1 = leaf21;
            *leaf2 = leaf22;
            *res = res2;
        }
        else if (res1 == nullptr) {
            *leaf1 = leaf11;
            *leaf2 = leaf21;
            if(*leaf1 != nullptr && *leaf2 != nullptr)
                *res = root;
        }
        else if (min(leaf11->second, leaf12->second) >= max(leaf21->second, leaf22->second)) {
            *leaf1 = leaf11;
            *leaf2 = leaf12;
            *res = res1;
        }
        else if (min(leaf21->second, leaf22->second) >= max(leaf11->second, leaf12->second)) {
            *leaf1 = leaf21;
            *leaf2 = leaf22;
            *res = res2;
        }
        else {
            vector<pair<TreeNode*, int>*> arr = { leaf12,leaf11,leaf21,leaf22 };
            sort(arr.begin(), arr.end(), [](pair<TreeNode*, int>* l1, pair<TreeNode*, int>* l2) {
                if (l1 == nullptr) {
                    return false;
                }
                else if (l2 == nullptr) {
                    return true;
                }
                return l1->second > l2->second;
                });
            *leaf1 = arr[0];
            *leaf2 = arr[1];
            *res = root;
        }
    }
};


int main() {
    TreeNode* root = wx::create_tree_int("[0,1,3,null,2]");
    Solution test;
    std::cout << test.lcaDeepestLeaves(root)->val;
    return 0;
}