#include<iostream>
#include<queue>
#include<unordered_map>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    
}; class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (root == nullptr) {
            return "";
        }
        stringstream res;
        //²ã´Î±éÀú
        queue<TreeNode**> q;
        q.push(&root);
        while (!q.empty()) {
            TreeNode** node = q.front();
            q.pop();
            if (*node == nullptr) {
                res << "null,";
            }
            else {
                res << (*node)->val << ",";
                q.push(&((*node)->left));
                q.push(&((*node)->right));
            }
        }
        return res.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return nullptr;
        }
        vector<string> data_v = split(data, ',');
        queue<TreeNode**> q;
        int i = 0;
        TreeNode* root = new TreeNode(atoi(data_v[i++].c_str()));
        q.push(&(root->left));
        q.push(&(root->right));
        while (i < data_v.size()) {
            TreeNode** node = q.front();
            q.pop();
            string& s = data_v[i++];
            if (s == "null") {
                continue;
            }
            else {
                *node = new TreeNode(atoi(s.c_str()));
                q.push(&((*node)->left));
                q.push(&((*node)->right));
            }
        }
        return root;
    }
private:
    vector<string> split(string& s, char c) {
        vector<string> res;
        int begin = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == c && i != begin) {
                res.push_back(s.substr(begin, i - begin));
                begin = i + 1;
            }
        }
        if (begin != s.size()) {
            res.push_back(s.substr(begin));
        }
        return res;
    }
};

int main() {
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    Codec cc;
    string s = cc.serialize(root);
    TreeNode* t2 = cc.deserialize(s);
    return 0;
}

