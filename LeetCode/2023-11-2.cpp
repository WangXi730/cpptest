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
        //所有人都得每次进入遍历，效率太低了，所以我决定使用树状或者链表结构完成这件事
        vector<list<int>> tree(n);
        for (int i = 0; i < n; ++i) {
            if (favorite[favorite[i]] == i) {
                if (favorite[i] > i) {
                    cp.emplace_back(i, favorite[i]);
                }
            }
            else {
                //tree服务于线性体系，popular服务于环形体系，但当前无法区分，所以同时进行
                tree[favorite[i]].push_back(i);
                ++popular[favorite[i]];
            }
        }
        //如果有cp在，可以直接直线推进，而无需组成环
        int res = 0;
        for (auto& e : cp) {
            int res_i1 = 1;
            int res_i2 = 1;
            dfs(res_i1, e.first, 1, tree, popular);
            dfs(res_i2, e.second, 1, tree, popular);
            res += res_i1 + res_i2;
        }
        //去除所有没人喜欢的人的喜欢：他们的喜欢已经没有价值了，进入线性体系的人也没必要研究了
        //优化
        queue<int> loser;
        for (int i = 0; i < n; ++i) {
            if (popular[i] == 0) {
                loser.push(i);
            }
        }
        while (!loser.empty()) {
            int tmp = loser.front();
            loser.pop();
            if (--popular[favorite[tmp]] == 0) {
                //如果是线性体系的，那么就直接是-1了，不会反复进入这里
                loser.push(favorite[tmp]);
            }
        }
        vector<bool> used(n, false);
        for (int i = 0; i < n; ++i) {
            if (popular[i] <= 0) {
                used[i] = true;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (used[i]) {
                continue;
            }
            used[i] = true;
            //dfs(res, used, favorite, i, i, favorite[i], 2);
            int j = favorite[i];
            used[j] = true;
            int t_count = 1;
            while (j != i) {
                j = favorite[j];
                used[j] = true;
                ++t_count;
            }
            res = max(res, t_count);
        }
        return res;
    }
private:
    //直线扩张，原理就是找最深树
    void dfs(int& res, int root, int deep, vector<list<int>>& tree, vector<int>&popular) {
        //线性体系无法进入环形体系，所以在这里把所有线性体系的人去除，虽然这么做耦合度会提高，但为了效率
        popular[root] = 0;
        res = max(deep, res);
        for (auto& child : tree[root]) {
            dfs(res, child, deep + 1, tree, popular);
        }
    }
};

int main() {
    Solution test;
    vector<int> favorite{ 1,0,0,2,1,4,7,8,9,6,7,10,8};
    //wx::create("[3,4,7,4,6,2,4,3,2]", favorite);
    cout << test.maximumInvitations(favorite);
    return 0;
}



