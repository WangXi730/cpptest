#include"LeetCodeTools.hpp"

leetcode

class Solution {
public:
    int maximumInvitations(vector<int>& favorite) {
        //以每一个元素为第一个邀请的人，都试一遍
        //进行剪枝：收集所有人被多少人喜欢
        int n = favorite.size();
        vector<int> popular(n, 0);
        vector<pair<int, int>> cp;//互相喜欢的可以组成cp
        vector<bool> is_cp(n, false);
        for (int i = 0; i < n; ++i) {
            if (favorite[favorite[i]] == i && favorite[i] > i) {
                cp.emplace_back(i, favorite[i]);
                is_cp[i] = true;
                is_cp[favorite[i]] = true;
            }
            ++popular[favorite[i]];
        }
        //如果有cp在，可以直接直线推进，而无需组成环
        int res = 0;
        vector<bool> used(n, false);
        for (auto& e : cp) {
            int res_i1 = 1;
            int res_i2 = 1;
            for (int i = 0; i < n; ++i) {
                if (favorite[i] == e.first && i != e.second) {
                    dfs(res_i1, i, 2, favorite);
                }
                if (favorite[i] == e.second && i != e.first) {
                    dfs(res_i2, i, 2, favorite);
                }
            }
            res += res_i1 + res_i2;
        }
        //去除所有没人喜欢的人的喜欢：他们的喜欢已经没有价值了
        while (1) {
            bool end = true;
            for (int i = 0; i < n; ++i) {
                if (popular[i] == 0) {
                    popular[i] = -1;
                    --popular[favorite[i]];
                    end = false;
                }
            }
            if (end) {
                break;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (popular[i] <= 0) {
                used[i] = true;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (popular[i] <= 0) {
                continue;
            }
            used[i] = true;
            used[favorite[i]] = true;
            dfs(res, used, favorite, i, i, favorite[i], 2);
            used[i] = false;
            used[i] = false;
        }
        return res;
    }
private:
    //直线扩张，原理就是找最深树
    void dfs(int& res, int root, int deep, vector<int>& favorite) {
        res = max(deep, res);
        for (int child = 0; child < favorite.size(); ++child) {
            if (favorite[child] = root) {
                dfs(res, child, deep + 1, favorite);
            }
        }
    }
    //环状扩张
    void dfs(int& res, vector<bool>& used, vector<int>& favorite, int left, int right, int i, int tmp_res) {
        //如果左边的人就是i喜欢的，那么接下来可以尝试所有人作为接下来的人选，同时进行一次记录
        if (left == favorite[i]) {
            //记录
            res = max(res, tmp_res);
            //继续
            for (int j = 0; j < used.size(); ++j) {
                //如果这个人没有上桌，就可以上桌了
                if (!used[j]) {
                    used[j] = true;
                    dfs(res, used, favorite, i, right, j, tmp_res + 1);
                    used[j] = false;
                }
            }
        }
        else if (right == favorite[i]) {
            //结束，记录并返回
            res = max(res, tmp_res);
            return;
        }
        else {
            //还能继续拉人，尝试满足i
            if (!used[favorite[i]]) {
                used[favorite[i]] = true;
                dfs(res, used, favorite, i, right, favorite[i], tmp_res + 1);
                used[favorite[i]] = false;
            }
        }
    }
};


int main() {
    Solution test;
    vector<int> favorite{ 2,2,1,2 };
    //wx::create("[3,4,7,4,6,2,4,3,2]", favorite);
    cout << test.maximumInvitations(favorite);
    return 0;
}



