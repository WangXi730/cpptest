#include"LeetCodeTools.hpp"
leetcode
class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n,vector<int>(n));
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                dp[i][j] = nums[i] * nums[j];
            }
        }
        unordered_map<int,int> umap;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                ++umap[dp[i][j]];
            }
        }
        int res = 0;
        for (auto& e : umap) {
            res += e.second * (e.second - 1) * 4;
        }
        return res;
    }
public:
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int numWanted, int useLimit) {
        int n = values.size();
        vector<int> ordered_v(n, 0);
        for (int i = 1; i < n; ++i) {
            ordered_v[i] = i;
        }
        sort(ordered_v.begin(), ordered_v.end(), [=](int a, int b) {
            return values[a] > values[b];
            });
        int res = 0;
        unordered_map<int, int> hash;
        int i = 0;
        while (numWanted && i < n) {
            if (hash[labels[ordered_v[i]]] < useLimit) {
                ++hash[labels[ordered_v[i]]];
                res += values[ordered_v[i]];
                --numWanted;
            }
            ++i;
        }
        return res;
    }
    
};

int main() {
    Solution test;
    vector<int> values{ 5,4,3,2,1 };
    vector<int> labels{ 1,1,2,2,3 };

    test.largestValsFromLabels(values, labels, 3, 1);
    return 0;
}
