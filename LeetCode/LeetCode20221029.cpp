#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Solution {
public:
    //bool isScramble(string s1, string s2) {
    //    if (s1.size() == 1) {
    //        if (s1 != s2) {
    //            return false;
    //        }
    //        return true;
    //    }
    //    int size = 0;
    //    int hash1[26] = { 0 };
    //    int hash2[26] = { 0 };
    //    //正方向切
    //    for (int i = 0; i < s1.size() - 1; ++i) {
    //        ++hash1[s1[i] - 'a'];
    //        ++hash2[s2[i] - 'a'];
    //        if (hash1[s1[i] - 'a'] == hash2[s1[i] - 'a'] && hash1[s2[i] - 'a'] == hash2[s2[i] - 'a']) {
    //            if (isScramble(s1.substr(0, i + 1), s2.substr(0, i + 1)) && isScramble(s1.substr(i + 1), s2.substr(i + 1))) {
    //                return true;
    //            }
    //        }
    //    }
    //    //反方向切
    //    memset(hash1, 0, sizeof(int) * 26);
    //    memset(hash2, 0, sizeof(int) * 26);
    //    for (int i = 0; i < s1.size() - 1; ++i) {
    //        ++hash1[s1[i] - 'a'];
    //        ++hash2[s2[s2.size() - 1 - i] - 'a'];
    //        if (hash1[s1[i] - 'a'] == hash2[s1[i] - 'a'] && hash1[s2[s2.size() - 1 - i] - 'a'] == hash2[s2[s2.size() - 1 - i] - 'a']) {
    //            if (isScramble(s1.substr(0, i + 1), s2.substr(s2.size() - i - 1)) && isScramble(s1.substr(i + 1), s2.substr(0, s2.size() - i - 1))) {
    //                return true;
    //            }
    //        }
    //    }
    //    return false;
    //}
    bool isScramble(string s1, string s2) {
        if (s1 == s2) {
            return true;
        }
        int hash[26] = {0};
        for (int i = 0; i < s1.size(); ++i) {
            ++hash[s1[i] - 'a'];
            --hash[s2[i] - 'a'];
        }
        for (int i = 0; i < 26; ++i) {
            if (hash[i] != 0) {
                return false;
            }
        }
        for (int i = 1; i < s1.size(); ++i) {
            if ((isScramble(s1.substr(0, i), s2.substr(0, i)) && isScramble(s1.substr(i), s2.substr(i))) || isScramble(s1.substr(0, i), s2.substr(s1.size() - i)) && isScramble(s1.substr(i), s2.substr(0, s1.size() - i))) {
                return true;
            }
        }
        return false;
    }
public:
    vector<int> grayCode(int n) {
        //arr[i] 为 2^i
        vector<int> arr(n);
        arr[0] = 1;
        for (int i = 1; i < n; ++i) {
            arr[i] = arr[i - 1] * 2;
        }
        vector<int> res(arr[n - 1] * 2);
        for (int i = 0; i < res.size(); ++i) {
            for (int j = 0; j < n; ++j) {
                if (i/arr[j] == 0) {
                    break;
                }
                int t = (i / arr[j]) % 4;
                if (t == 1 || t == 2) {
                    res[i] |= 1 << j;
                }
                else {
                    res[i] &= ~(1 << j);
                }
            }
        }
        return res;
    }
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> tmp;
        func(res, tmp, nums, 0);
        return res;
    }
private:
    void func(vector<vector<int>>& res, vector<int>& tmp, vector<int>& nums, int i) {
        res.push_back(tmp);
        if (i == nums.size()) {
            return;
        }
        for (int j = i; j < nums.size(); ++j) {
            if (j != i && nums[j] == nums[j - 1]) {
                continue;
            }
            tmp.push_back(nums[j]);
            func(res, tmp, nums, j+1);
            tmp.pop_back();
        }
    }
};

int main() {
    Solution test;
    vector<int> nums{ 4,4,4,1,4};
    test.subsetsWithDup(nums);
    return 0;
}
