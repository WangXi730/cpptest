#include<iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int maxCoins(vector<int>& nums) {
        vector<vector<int>> dp(nums.size() + 1, vector<int>(nums.size() + 1));
        for (int step = 1; step <= nums.size(); ++step) {
            for (int inf = 0; inf + step <= nums.size(); ++inf) {
                if (step == 1) {
                    dp[inf][inf + step] = nums[inf];
                    continue;
                }
                for (int k = inf; k < inf + step; ++k) {
                    int tmp = nums[k];
                    if (k > inf) {
                        tmp *= nums[k - 1];
                    }
                    if (k < inf + step - 1) {
                        tmp *= nums[k + 1];
                    }
                    dp[inf][inf + step] = max(dp[inf][inf + step], dp[inf][k] + dp[k + 1][inf + step] + tmp);
                }
            }
        }
        return dp[0][nums.size()];
    }
};

int main() {
    vector<int> nums{ 3,1,5,8 };
    Solution test;
    test.maxCoins(nums);
    return 0;
}