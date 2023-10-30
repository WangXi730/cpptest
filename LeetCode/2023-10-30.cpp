#include"LeetCodeTools.hpp"

leetcode

class Solution {
public:
    int maxRepOpt1(string text) {
        int res = 0;
        vector<int> hash_count(26, 0);
        for (int i = 0; i < text.size(); ++i) {
            ++hash_count[text[i] - 'a'];
        }
        int j = 0;
        int diff_idx = -1;
        int i = 0;
        for (i = 0; i < text.size(); ++i) {
            if (text[i] != text[j]) {
                if (diff_idx != -1) {
                    res = max(res, min(i - j, hash_count[text[j] - 'a']));
                    if (i - diff_idx == 1) {
                        if (text[diff_idx] != text[i]) {
                            j = diff_idx;
                            diff_idx = i;
                        }
                        else {
                            j = diff_idx;
                            diff_idx = -1;
                        }
                    }
                    else {
                        if (text[diff_idx] == text[i] && diff_idx + 2 == i) {
                            j = diff_idx++;
                        }
                        else {
                            j = diff_idx + 1;
                            diff_idx = i;
                        }
                    }
                }
                else {
                    diff_idx = i;
                }
            }
        }
        if (diff_idx == -1) {
            res = max(res, min(i - j + 1, hash_count[text[j] - 'a']));
        }
        else {
            res = max(res, min(i - j, hash_count[text[j] - 'a']));
        }
        return res;
    }
public:
    int distinctAverages(vector<int>& nums) {
        unordered_map<double, int> umap;
        int count = 0;
        sort(nums.begin(), nums.end());
        int i = 0;
        int j = nums.size() - 1;
        while (j > i) {
            ++umap[((double)nums[i++] + nums[j--]) / 2];
        }
        for (auto& e : umap) {
            if (e.second > count) {
                count = e.second;
            }
        }
        return count;
    }
public:
    int equalPairs(vector<vector<int>>& grid) {
        vector<vector<int>> trans = transpose(grid);
        int res = 0;
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid.size(); ++j) {
                if (grid[i] == trans[j]) {
                    ++res;
                }
            }
        }
        return res;
    }
private:
    vector<vector<int>> transpose(vector<vector<int>>& grid) {
        vector<vector<int>> res(grid[0].size(), vector<int>(grid.size()));
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                res[j][i] = grid[i][j];
            }
        }
        return res;
    }
public:
    Solution() :dp(1, vector<int>(1)) {
        m_ = 0;
        n_ = 0;
    }
    int tilingRectangle(int n, int m) {
        int n1 = max(n, m);
        int m1 = min(n, m);
        n = n1;
        m = m1;
        if (n <= n_ && m <= m_) {
            return dp[n][m];
        }
        //修改dp容量
        dp.resize(n + 1);
        for (int i = 0; i < n + 1; ++i) {
            dp[i].resize(m + 1);
        }
        //dp扩容
        for (int j = 1; j < m + 1; ++j) {
            for (int i = 1; i < n + 1; ++i) {
                if (i < n_ + 1 && j < m_ + 1) {
                    continue;
                }
                if (i < j) {
                    dp[i][j] = dp[j][i];
                }
                else if (j == i) {
                    dp[i][j] = 1;
                    continue;
                }
                else if (i % j == 0) {
                    dp[i][j] = i / j;
                }
                else {
                    //分为两份
                    dp[i][j] = 999;
                    for (int t1 = 1; t1 <= i / 2; ++t1) {
                        dp[i][j] = min(dp[i][j], dp[t1][j] + dp[i - t1][j]);
                    }
                    for (int t2 = 1; t2 <= j / 2; ++t2) {
                        dp[i][j] = min(dp[i][j], dp[i][t2] + dp[i][j - t2]);
                    }
                    //分成5份
                    for (int t1_i = 1; t1_i < i - 1; ++t1_i) {
                        for (int t1_j = 2; t1_j < j; ++t1_j) {
                            for (int t2_j = 1; t2_j < t1_j; ++t2_j) {
                                for (int t3_i = 1 + t1_i; t3_i < i; ++t3_i) {
                                    dp[i][j] = min(dp[i][j], dp[t1_i][t1_j] + dp[i - t1_i][t2_j] + dp[t3_i][j - t1_j] + dp[i - t3_i][j - t2_j] + dp[t3_i - t1_i][t1_j - t2_j]);
                                }
                            }
                        }
                    }
                }
            }
        }
        return dp[n][m];
    }
private:
    vector<vector<int>> dp;
    int m_, n_;
    public:
        int unequalTriplets(vector<int>& nums) {
            int res = 0;
            int n = nums.size();
            for (int i = 0; i < n; ++i) {
                for (int j = i + 1; j < n; ++j) {
                    for (int k = j + 1; k < n; ++k) {
                        if (nums[i] != nums[j] && nums[j] != nums[k] && nums[i] != nums[k]) {
                            ++res;
                        }
                    }
                }
            }
            return res;
        }
};

int main() {
    Solution test;
    string t = "aaaaa";
    //test.maxRepOpt1(t);
    vector<int> nums;
    wx::create("[0,0,7,2]", nums);
    //test.distinctAverages(nums);
    vector<vector<int>> grid;
    wx::create("[[3,2,1],[1,7,6],[2,7,7]]", grid);
    test.equalPairs(grid);
    test.tilingRectangle(2, 3);
    vector<int> n = { 4,4,2,4,3 };
    test.unequalTriplets(n);
    return 0;
}