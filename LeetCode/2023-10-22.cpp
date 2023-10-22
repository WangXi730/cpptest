#include"LeetCodeTools.hpp"

leetcode
using TreeNode = wx::TreeNode<int>;
class Solution {
public:
    int maxSatisfaction(vector<int>& satisfaction) {
        sort(satisfaction.begin(), satisfaction.end());
        int n = satisfaction.size();
        vector<int> dp(n, 0);
        dp[n - 1] = satisfaction[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            dp[i] = dp[i + 1] + satisfaction[i];
        }
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res += (i + 1) * satisfaction[i];
        }
        for (int i = 0; i < n; ++i) {
            if (dp[i] < 0) {
                res -= dp[i];
            }
        }
        return res;
    }
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        vector<int> pre = { 0 };
        for (int i = 0; i < mat.size(); ++i) {
            vector<int> nums;
            for (auto& it : pre) {
                for (auto& it2 : mat[i]) {
                    nums.push_back(it + it2);
                }
            }
            sort(nums.begin(), nums.end());
            if(nums.size() > k)
                nums.resize(k);
            nums.swap(pre);
        }
        return pre[k - 1];
    }
public:
    int averageValue(vector<int>& nums) {
        int res = 0;
        int count = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] % 2 == 0 && nums[i] % 3 == 0) {
                res += nums[i];
                ++count;
            }
        }
        if (count == 0) {
            return 0;
        }
        return res / count;
    }
public:
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        unordered_set<int> uset;
        for (auto& e : to_delete) {
            uset.insert(e);
        }
        vector<TreeNode*> res;
        queue<pair<TreeNode*, TreeNode*>> q;
        q.push(make_pair(root, nullptr));
        while (!q.empty()) {
            TreeNode* node = q.front().first;
            TreeNode* pr = q.front().second;
            q.pop();
            if (uset.find(node->val) != uset.end()) {
                if (pr != nullptr && pr->left == node) {
                    pr->left = nullptr;
                }
                else if (pr != nullptr) {
                    pr->right = nullptr;
                }
                if (node->left != nullptr) {
                    q.push(make_pair(node->left, nullptr));
                    node->left = nullptr;
                }
                if (node->right != nullptr) {
                    q.push(make_pair(node->right, nullptr));
                    node->right = nullptr;
                }
                continue;
            }
            else if (pr == nullptr) {
                res.push_back(node);
            }
            if (node->left != nullptr) {
                q.push(make_pair(node->left, node));
            }
            if (node->right != nullptr) {
                q.push(make_pair(node->right, node));
            }
        }
        return res;
    }
};


int main() {
    Solution test;
    vector<int> arr{ -1,-8,0,5,-7 };

    test.maxSatisfaction(arr);
    vector<vector<int>> mat;
    wx::create("[[1,10,10],[1,4,5],[2,3,6]]", mat);
    test.kthSmallest(mat,14);
    vector<int> nums;
    wx::create("[1,2,4,7,10]", nums);
    test.averageValue(nums);



    TreeNode* root = nullptr;
    wx::create("[1,2,3,4,5,6,7]", root);
    vector<int> to_del{3,5};
    test.delNodes(root, to_del);
    return 0;
}