#include"LeetCodeTools.hpp"

leetcode
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
};


int main() {
    Solution test;
    vector<int> arr{ -1,-8,0,5,-7 };

    test.maxSatisfaction(arr);
    vector<vector<int>> mat;
    wx::create("[[1,10,10],[1,4,5],[2,3,6]]", mat);
    cout << test.kthSmallest(mat,14);
    return 0;
}