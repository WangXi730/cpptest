#include"LeetCodeTools.hpp"
leetcode

class Solution {
public:
    struct TreeNode {
        TreeNode(int v) : value(v) {}
        void insert(int data) {
            if (value == 0) {
                return;
            }
            if (data & value) {
                if (left == nullptr)left = new TreeNode(value >> 1);
                left->insert(data);
            }
            else {
                if (right == nullptr)right = new TreeNode(value >> 1);
                right->insert(data);
            }
        }
        void search(int& data) {
            if (value == 0) {
                return;
            }
            if (!(data & value) && left != nullptr) {
                //该位为0，且存在该位为1的数字
                data |= value;
                left->search(data);
                //剪枝
                return;
            }
            else if ((data & value) && right != nullptr) {
                //该位为1，且存在该位为0的数字
                right->search(data);
                //剪枝
                return;
            }
            if (left != nullptr) {
                data &= ~value;
                left->search(data);
            }
            if (right != nullptr) {
                data &= ~value;
                right->search(data);
            }
        }
        int value = 0;
        TreeNode* left = nullptr;
        TreeNode* right = nullptr;
    };
    int findMaximumXOR(vector<int>& nums) {
        TreeNode root(1 << 30);
        for (auto& e : nums)root.insert(e);
        for (auto& e : nums)root.search(e);
        sort(nums.begin(), nums.end());
        return *nums.rbegin();
    }
};

int main() {
    vector<int> nums;
    wx::create("[3,10,5,25,2,8]", nums);
    Solution t;
    cout << t.findMaximumXOR(nums);
	return 0;
}
