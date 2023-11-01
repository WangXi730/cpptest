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
                //if (p_[a] == b) {
                //}
                a = p_[a];
                    //return false;
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
        //myFunc f(parents);
        sort(sorted_node.begin(), sorted_node.end(),[&](int a, int b) {
            int c = a;
            while (parents[c] != -1) {
                if (parents[c] == b) {
                    return false;
                }
                c = parents[c];
            }
            return true;
            });
            
        vector<set<int>> sets(n);
        vector<int> ans(n,1);
        for (int i = n - 1; i >= 0; --i) {
            int node = sorted_node[i];
            //�Ȱ���ε�Ԫ����ӽ�ȥ
            sets[node].insert(nums[node]);
            //��ʼ�������ҵ���һ�������ڵ�Ԫ��
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
            //������һ�����ڵ��set
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