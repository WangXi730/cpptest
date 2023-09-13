#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    long long repairCars(vector<int>& ranks, int cars) {
        vector<int> dp(ranks.size(), 0);
        for (int i = 0; i < cars; ++i) {
            int idx = 0;
            for (int j = 1; j < ranks.size(); ++j) {
                if (ranks[j] * (dp[j] + 1) * (dp[j] + 1) < ranks[idx] * (dp[idx] + 1) * (dp[idx] + 1)) {
                    idx = j;
                }
            }
            ++dp[idx];
        }
        int res = 0;
        for (int i = 0; i < ranks.size(); ++i) {
            res = max(res, dp[i] * dp[i] * ranks[i]);
        }
        return res;
    }
};

int main() {
    vector<int> arr{4, 2, 3, 1};
    Solution test;
    cout << test.repairCars(arr, 10);
    return 0;
}