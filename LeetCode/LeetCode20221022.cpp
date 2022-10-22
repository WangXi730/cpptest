#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Solution {
public:
//44. ͨ���ƥ��
    bool isMatch(string s, string p) {
        vector<vector<bool>>dp(s.size() + 1, vector<bool>(p.size() + 1, false));
        //dp[i][j]����s��ǰi���ַ��Ƿ�ƥ��p��ǰj���ַ�
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
//45. ��Ծ��Ϸ II
    int jump(vector<int>& nums) {
        //dp[i]��ʾ���λ��������Ҫ����
        vector<int> dp(nums.size(), -1);
        //��ʼλ��Ϊ0������dp[0] = 0;
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