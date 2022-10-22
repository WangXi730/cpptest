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
};



int main() {
    Solution test;
    test.isMatch("abefcdgiescdfimde", "ab*cd?i*de");
    return 0;
}