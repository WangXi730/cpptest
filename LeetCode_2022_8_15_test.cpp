#include<iostream>
#include<json/json.h>
#include<sstream>
#include<string>
#include<queue>
#include<memory>
using namespace std;
//class Solution {
//public:
//    string reverseWords(string s) {
//        string res;
//        int j = s.size() - 1;
//        int i = 0;
//        while (s[j] == ' ') {
//            --j;
//        }
//        while (j >= 0) {
//            while (j>=0&&s[j] != ' ') {
//                res.push_back(s[j--]);
//            }
//            while (j>=0&&s[j] == ' ') {
//                --j;
//            }
//            _reverse(res, i, res.size() - 1);
//            if (j >= 0) {
//                res.push_back(' ');
//                i = res.size();
//            }
//        }
//        return res;
//    }
//private:
//    void _reverse(string& s, int first, int last) {
//        while (last > first) {
//            char c = s[first];
//            s[first] = s[last];
//            s[last] = c;
//            ++first;
//            --last;
//        }
//    }
//};
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        if (nums.empty()) {
            return vector<int>();
        }
        vector<int> res(nums.size()-k+1);
        res[0] = nums[0];
        int sig = 0;
        for (int i = 1; i < k; ++i) {
            if (nums[i] > res[0]) {
                res[0] = nums[i];
                sig = 1;
            }
            else if (nums[i] == res[0]) {
                sig += 1;
            }
        }
        for (int i = 1; i < nums.size() - k + 1; ++i) {
            if (nums[i + k - 1] > res[i - 1]) {
                res[i] = nums[i + k - 1];
                sig = 1;
            }
            else if (nums[i - 1] < res[i - 1]) {
                res[i] = res[i - 1];
            }
            else if (nums[i + k - 1] == res[i - 1]) {
                sig += 1;
                res[i] = res[i - 1];
                if (nums[i - 1] == res[i - 1]) {
                    sig -= 1;
                }
            }
            else {
                if (sig > 1) {
                    sig -= 1;
                    res[i] = res[i - 1];
                }
                else {
                    res[i] = nums[i];
                    for (int j = 1; j < k; ++j) {
                        if (res[i] < nums[i + j]) {
                            res[i] = nums[i + j];
                            sig = 1;
                        }
                        else if (res[i] == nums[i + j]) {
                            sig += 1;
                        }
                    }
                }
            }
        }
        return res;
    }
};
//力扣剑指60，n个骰子的可能性
vector<double> dicesProbability(int n) {
    vector<double> res(5 * n + 1);
    vector<vector<double>> dp(n, vector<double>(6 * n));
    int all = 1;
    for (int i = 0; i < n; ++i) {
        all *= 6;
    }
    for (int i = 0; i < 6; ++i) {
        dp[0][i] = 1;
    }
    //i表示行
    for (int i = 1; i < n; ++i) {
        //i+j表示总点数
        for (int j = 1; j <= 5*i+6; ++j) {
            //k表示这个骰子的点数
            for (int k = 1; k <= 6; ++k) {
                if (k < i + j) {
                    dp[i][i + j - 1] += dp[i - 1][i + j - 1 - k];
                }
            }
        }
    }
    for (int i = 0; i < 5 * n + 1; ++i) {
        res[i] = dp[n - 1][i + n - 1] / all;
    }
    return res;
}
int main() {/*
    Solution a;
    vector<int> test{ 4,-2 };
    a.maxSlidingWindow(test,2);*/
    dicesProbability(2);
    return 0;    
}


