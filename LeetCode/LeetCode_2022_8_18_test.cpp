#include<iostream>
#include<vector>
#include<list>
#include<unordered_map>
using namespace std;


class Solution {
//��ָ Offer 67. ���ַ���ת��������
public:
    int strToInt(string str) {
        int i = 0;
        int f = 1;
        while (str[i] == ' ') {
            ++i;
        }
        if (str[i] == '+') {
            ++i;
        }
        else if (str[i] == '-') {
            ++i;
            f = -1;
        }
        else if (str[i] < '0' || str[i]>'9') {
            return 0;
        }

        int j = i;
        while (str[j] >= '0' && str[j] <= '9') {
            ++j;
        }
        while (str[i] == '0') {
            ++i;
        }
        string s(str.begin() + i, str.begin() + j);
        if (s.size() == 10) {
            if (f > 0) {
                if (s >= "2147483647") {
                    return 2147483647;
                }
            }
            else {
                if (s >= "2147483648") {
                    return -2147483648;
                }
            }
        }
        else if (s.size() > 10) {
            if (f > 0) {
                return 2147483647;
            }
            else {
                return -2147483648;
            }
        }
        int res = 0;
        while (i < j) {
            res = res * 10 + (str[i] - '0');
            ++i;
        }
        return res * f;
    }
//��ָ Offer 68 - I. �����������������������
public:
    struct TreeNode {
        int val;
        TreeNode* left;
        TreeNode* right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
    TreeNode* lowestCommonAncestor1(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (p == q) {
            return q;
        }
        else if (q == p->left || q == p->right) {
            return p;
        }
        else if (p == q->left || p == q->right) {
            return q;
        }
        else if (p == root) {
            return p;
        }
        else if (q == root) {
            return q;
        }
        //���ڲ����������������Ҹ��ڵ�ֻ��ͨ����ѯ�����㲢��¼���ַ�ʽ
        list<TreeNode*> v1;
        list<TreeNode*> v2;
        TreeNode* ptr = root;
        while (p != ptr) {
            v1.push_back(ptr);
            if (ptr->val > p->val) {
                ptr = ptr->left;
            }
            else {
                ptr = ptr->right;
            }
        }
        v1.push_back(p);
        ptr = root;
        while (q != ptr) {
            v2.push_back(ptr);
            if (ptr->val > q->val) {
                ptr = ptr->left;
            }
            else {
                ptr = ptr->right;
            }
        }
        v2.push_back(q);
        auto it1 = v1.rbegin();
        auto it2 = v2.rbegin();
        //��������ʼ�����������
        while ((*it1) != (*it2)) {
            if ((*it1) == root) {
                it1 = v2.rbegin();
                ++it2;
                continue;
            }
            else if ((*it2) == root) {
                it2 = v1.rbegin();
                ++it1;
                continue;
            }
            ++it1;
            ++it2;
        }
        return *it1;
    }
//��ָ Offer 68 - II. �������������������
public:
    TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
        //ʹ����һ���˼�룬ֻ�����������Ĳ�ѯ��ʽ������һ���ı仯
        //������������ѯ
        list<TreeNode*> v1;
        _query_node(root, v1, p);
        list<TreeNode*> v2;
        _query_node(root, v2, q);
        //ʣ�µľ�һ����
        //��������ʼ�����������
        auto it1 = v1.begin();
        auto it2 = v2.begin();
        while ((*it1) != (*it2)) {
            if ((*it1) == root) {
                it1 = v2.begin();
                ++it2;
                continue;
            }
            else if ((*it2) == root) {
                it2 = v1.begin();
                ++it1;
                continue;
            }
            ++it1;
            ++it2;
        }
        return *it1;

    }
private:
    bool _query_node(TreeNode* node, list<TreeNode*>& l, TreeNode* q_node) {
        if (node == nullptr) {
            return false;
        }
        if (node == q_node || _query_node(node->left, l, q_node) || _query_node(node->right, l, q_node)) {
            l.push_back(node);
            return true;
        }
        return false;
    }
public:
    TreeNode* lowestCommonAncestor3(TreeNode* root, TreeNode* p, TreeNode* q) {
        unordered_map<TreeNode*, bool> mp;
        TreeNode* res;
        _query_node3(root, p, mp, res);
        _query_node3(root, q, mp, res);
        return res;
    }
private:
    bool _query_node3(TreeNode* node, TreeNode*& q_node, unordered_map<TreeNode*, bool>& mp, TreeNode*& res) {
        if (node == nullptr) {
            return false;
        }
        if (node == q_node || _query_node3(node->left, q_node, mp, res) || _query_node3(node->right, q_node, mp, res)) {
            if (mp[node]) {
                res = node;
                return false;
            }
            mp[node] = true;
            return true;
        }
        return false;
    }
};

int main() {
    Solution a;
    a.strToInt("20000000000000000000");
    Solution::TreeNode root(3);
    root.left = new Solution::TreeNode(5);
    root.right = new Solution::TreeNode(1);
    root.left->left = new Solution::TreeNode(6);
    root.left->right = new Solution::TreeNode(2);
    root.right->left = new Solution::TreeNode(0);
    root.right->right = new Solution::TreeNode(8);
    root.right->right->left = new Solution::TreeNode(7);
    root.right->right->right = new Solution::TreeNode(4);
    a.lowestCommonAncestor3(&root, root.left, root.right->right->right);

    return 0;
}