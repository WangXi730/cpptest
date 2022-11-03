#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


// Definition for singly-linked list.
 struct ListNode {
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
 };
 

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
    TreeNode* sortedListToBST(ListNode* head) {
        vector<int> nums;
        while (head != nullptr) {
            nums.push_back(head->val);
            head = head->next;
        }
        return sortedArrayToBST(nums);
    }
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        vector<int> inorder = nums;
        sort(inorder.begin(), inorder.end());
        TreeNode* res;
        _insert(res, -1, inorder.size(), inorder);
        return res;
    }
private:
    void _insert(TreeNode*& node, int left, int right, vector<int>& inorder) {
        if (left >= right - 1) {
            return;
        }
        int mid = (left + right) / 2;
        node = new  TreeNode(inorder[mid]);
        _insert(node->left, left, mid, inorder);
        _insert(node->right, mid, right, inorder);
    }
};


int main() {
    ListNode* head = new ListNode(-10);
    head->next = new ListNode(-3);
    head->next->next = new ListNode(0);
    head->next->next->next = new ListNode(5);
    head->next->next->next->next = new ListNode(9);
    Solution test;
    test.sortedListToBST(head);
    return 0;
}