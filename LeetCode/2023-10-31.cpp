#include"LeetCodeTools.hpp"


leetcode

class Solution {
public:
    struct myFunc
    {
        myFunc(vector<int>&p):p_(p){
        }
        bool operator()(int a, int b) {
            while (p_[a] != -1) {
                if (p_[a] == b) {
                    return false;
                }
                a = p_[a];
            }
            return true;
        }
        vector<int>& p_;
    };
    vector<int> smallestMissingValueSubtree(vector<int>& parents, vector<int>& nums) {
        int n = nums.size();
        vector<int> sorted_node(n);
        for (int i = 0; i < n; ++i) {
            sorted_node[i] = i;
        }
        myFunc f(parents);
        sort(sorted_node.begin(), sorted_node.end(), f);/*[&](int a, int b) {
            while (parents[a] != -1) {
                if (parents[a] == b) {
                    return false;
                }
                a = parents[a];
            }
            return true;
            });
            */
        vector<set<int>> sets(n);
        vector<int> ans(n,1);
        for (int i = n - 1; i >= 0; --i) {
            int node = sorted_node[i];
            //先把这次的元素添加进去
            sets[node].insert(nums[node]);
            //开始遍历，找到第一个不存在的元素
            auto e = sets[node].lower_bound(ans[node]);
            for (int j = ans[node]; j <= 10000; ++j) {
                if (*e != j) {
                    ans[node] = j;
                    break;
                }
                ++e;
                if (e == sets[node].end()) {
                    ans[node] = *sets[node].rbegin() + 1;
                    break;
                }
            }
            //创造下一个父节点的set
            if (parents[node] == -1) {
                continue;
            }
            ans[parents[node]] = max(ans[parents[node]],ans[node]);
            if (sets[parents[node]].size() == 0) {
                sets[parents[node]] = move(sets[node]);
            }
            else {
                for (auto& e : sets[node]) {
                    sets[parents[node]].insert(e);
                }
            }
        }
        return ans;
    }
};


int main() {
    vector<int> parents;
    vector<int> nums;
    wx::create("[-1,0,0,2]", parents);
    wx::create("[1,2,3,4]", nums);
    Solution test;
    test.smallestMissingValueSubtree(parents, nums);
    return 0;
}