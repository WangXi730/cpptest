#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<algorithm>
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
    //47. 全排列 II
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(),nums.end());
        vector<bool> used(nums.size(), false);
        vector<int> tmp(nums.size(), 0);
        func(used, nums, tmp, res, 0);
        return res;

    }
    void func(vector<bool>& used, vector<int>& nums, vector<int>& tmp, vector<vector<int>>& res, int i) {
        //递归退出条件
        if (i == used.size()) {
            res.push_back(tmp);
            return;
        }
        for (int j = 0; j < nums.size(); ++j) {
            //第j个元素没有被使用，那么就可以让这个元素填入i位置
            if (j && nums[j] == nums[j - 1] && !used[j-1]) {
                continue;
            }
            if (!used[j]) {
                used[j] = true;
                tmp[i] = nums[j];
                //递归
                func(used, nums, tmp, res, i + 1);
                //回溯
                used[j] = false;
            }
        }
    }
    void rotate(vector<vector<int>>& matrix) {
        //固定值i代表层
        for (int i = 0; i < matrix.size() / 2; ++i) {
            //偏移量j
            for (int j = 0; i + j < matrix[0].size() - i - 1; ++j) {
                int tmp = matrix[i][i + j];
                matrix[i][i + j] = matrix[matrix.size() - 1 - i - j][i];
                matrix[matrix.size() - 1 - i - j][i] = matrix[matrix.size() - 1 - i][matrix.size() - 1 - i - j];
                matrix[matrix.size() - 1 - i][matrix.size() - 1 - i - j] = matrix[i + j][matrix.size() - 1 - i];
                matrix[i + j][matrix.size() - 1 - i] = tmp;
            }
        }
    }
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        map<map<char, int>, vector<string>> mp;
        for (int i = 0; i < strs.size(); ++i) {
            map<char, int> tmp;
            int str_size = strs[i].size();
            for (int j = 0; j < str_size; ++j) {
                ++tmp[strs[i][j]];
            }
            mp[tmp].push_back(strs[i]);
        }
        vector<vector<string>> res;
        for (auto& e : mp) {
            res.push_back(e.second);
        }
        return res;

    }
    double myPow(double x, int n) {
        if (n < 0) {
            n = -n;
            x = 1 / x;
        }
        double res = 1;
        while (n--) {
            res *= x;
        }
        return res;
    }
};



int main() {
    Solution test;
    //test.isMatch("abefcdgiescdfimde", "ab*cd?i*de");
    //vector<int> tmp{ 1,1,2 };
    //test.permuteUnique(tmp);
    //vector<vector<int>> v{ {1,2,3},{4,5,6},{7,8,9} };
    //test.rotate(v);
    test.myPow(2.0, 10);
    return 0;
}