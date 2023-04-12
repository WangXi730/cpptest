#include<iostream>
#include<vector>
#include<unordered_set>
#include<map>
using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size(),1);
        dp[0] = 1;
        int res = 0;
        for (int i = 1; i < dp.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] > nums[j]) {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            res = max(res, dp[i]);
        }
        return res;
    }
public:    
    vector<string> removeInvalidParentheses(string s) {
    bool res_cond = false;
    vector<string> res;
    int lr = 0;
    int c_num = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '(') {
            ++lr;
        }
        else if(s[i] == ')') {
            --lr;
        }
        else {
            ++c_num;
        }
    }
    for (int rmnum = max(0, abs(lr)); rmnum < s.size() - c_num + 1; ++rmnum) {
        if (res_cond) {
            return res;
        }
        unordered_set<string> uset;
        string ts = "";
        dfs(uset, s, ts, 0, rmnum, lr);
        for (auto& e : uset) {
            if (valid(e)) {
                res_cond = true;
                res.push_back(e);
            }
        }
    }
    if (res.empty()) {
        return { "" };
    }
    return res;
    }
private:
    void dfs(unordered_set<string>& res, string& s, string& ts, int i, int rm, int lr) {
        if (rm == 0) {
            if (lr != 0) {
                return;
            }
            if (i == s.size()) {
                res.insert(ts);
            }
            else {
                res.insert(ts + s.substr(i));
            }
            return;
        }
        else if (i >= s.size()) {
            return;
        }
        else if (abs(lr) > rm) {
            return;
        }
        int lr_d = 0;
        if (s[i] == '(') {
            lr_d = -1;
        }
        else if (s[i] == ')') {
            lr_d = 1;
        }
        dfs(res, s, ts, i + 1, rm - 1, lr+lr_d);
        ts.push_back(s[i]);
        dfs(res, s, ts, i + 1, rm,lr);
        ts.pop_back();
    }
    //ÅÐ¶ÏÊÇ·ñÊÇÓÐÐ§À¨ºÅ×Ö·û´®
    bool valid(const string& s) {
        int left_stack = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (left_stack < 0) {
                return false;
            }
            else if (s[i] == '(') {
                ++left_stack;
            }
            else if (s[i] == ')') {
                --left_stack;
            }
        }
        return left_stack == 0;
    }
};


int main() {
    Solution test;
    test.removeInvalidParentheses("()())()");
    return 0;
}