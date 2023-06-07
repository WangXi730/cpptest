#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<set>
#include<unordered_map>
using namespace std;
class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        int n = tickets.size();
        vector<bool> trace(n, false);
        unordered_map<string, multimap<string, int>> umap;
        for (int i = 0; i < n; ++i) {
            umap[tickets[i][0]].insert(make_pair(tickets[i][1], i));
        }
        vector<string> res;
        dfs(tickets, umap, trace, res, 0, "JFK");
        reverse(res.begin(), res.end());
        return res;
    }
    void dfs(vector<vector<string>>& tickets, unordered_map<string, multimap<string, int>>& umap, vector<bool>& trace, vector<string>& res, int layer, const string& fromi) {
        if (layer == trace.size()) {
            res.emplace_back(fromi);
            return;
        }
        multimap<string, int>& ticket = umap[fromi];
        for (auto& toi : ticket) {
            if (trace[toi.second]) {
                continue;
            }
            trace[toi.second] = true;
            dfs(tickets, umap, trace, res, layer + 1, toi.first);
            trace[toi.second] = false;
            //检查是否已经找到通路，若找到，执行剪枝
            if (!res.empty()) {
                res.emplace_back(fromi);
                return;
            }
        }
    }
};

#include"LeetCode_array.hpp"

int main() {
    vector<vector<string>> tickets{ {"EZE","AXA"},{"TIA","ANU"},{"ANU","JFK"},{"JFK","ANU"},{"ANU","EZE"},{"TIA","ANU"},{"AXA","TIA"},{"TIA","JFK"},{"ANU","TIA"},{"JFK","TIA"} };
    Solution test;
    test.findItinerary(tickets);
    return 0;
}
