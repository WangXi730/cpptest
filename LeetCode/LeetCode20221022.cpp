#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Solution {
public:
//44. 通配符匹配
    bool isMatch(string s, string p) {
        vector<vector<bool>>dp(s.size() + 1, vector<bool>(p.size() + 1, false));
        //dp[i][j]代表s的前i个字符是否匹配p的前j个字符
        dp[0][0] = true;

        for (int i = 0; i <p.size(); ++i) {
            if (p[i] == '*') {
                dp[0][i + 1] = dp[0][i];
            }
        }
        for (int i = 1; i < s.size()+1; ++i) {
            for (int j = 1; j < p.size()+1; ++j) {
                if (s[i - 1] == p[j - 1] || p[j - 1] == '?') {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
                }
            }
        }
        return dp[s.size()][p.size()];
    }
//45. 跳跃游戏 II
    int jump(vector<int>& nums) {
        //dp[i]表示这个位置最少需要几步
        vector<int> dp(nums.size(), -1);
        //初始位置为0，所以dp[0] = 0;
        dp[0] = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] + i +1>= nums.size()) {
                return dp[i] + 1;
            }
            for (int j = i + 1; j < nums.size() && j - i <= nums[i]; ++j) {
                if (dp[j] == -1 || dp[j] > dp[i] + 1) {
                    dp[j] = dp[i] + 1;
                }
            }
        }
        return dp[nums.size() - 1];
    }
};



int main() {
    Solution test;
    //test.isMatch("abefcdgiescdfimde", "ab*cd?i*de");
    vector<int> tmp{ 2, 3, 1, 1, 4 };
    test.jump(tmp);
    return 0;
}