#include"LeetCodeTools.hpp"


leetcode

class Solution {
public:
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        int n = parents.size();
        vector<int> ans(n,1);
        int i = 0;
        for (i = 0; i < n; ++i) {
            if (nums[i] == 1) {
                break;
            }
        }
        if (i < n) {
            vector<bool> table(100001, false);
            vector<list<int>> tree(n);
            for (int j = 1; j < n; ++j) {
                tree[parents[j]].push_back(j);
            }
            dfs(i, table, tree, nums);
            int j = 1;
            while (table[j]) {
                ++j;
            }
            ans[i] = j;
            int pr = parents[i];
            while (pr != -1) {
                table[nums[pr]] = true;
                for (auto& e : tree[pr]) {
                    if (e != i) {
                        dfs(e, table, tree, nums);
                    }
                }
                while (table[j]) {
                    ++j;
                }
                ans[pr] = j;
                //迭代
                i = pr;
                pr = parents[i];
            }
        }
        return ans;
    }
private:
    void dfs(int root, vector<bool>& table, vector<list<int>>& tree, vector<int>&nums) {
        //访问
        table[nums[root]] = true;
        //遍历子节点
        for (auto& e : tree[root]) {
            dfs(e, table, tree, nums);
        }
    }
};
#include<fstream>

int main() {
    vector<int> parents;
    vector<int> nums;
    string ps;
    string ns;
    ifstream p;
    p.open("parents.txt", std::ios::in);
    ifstream n;
    n.open("nums.txt", std::ios::in);
    p >> ps;
    n >> ns;
    wx::create(ps, parents);
    wx::create(ns, nums);
    Solution test;
    test.smallestMissingValueSubtree(parents, nums);
    return 0;
}