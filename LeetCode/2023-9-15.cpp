#include<iostream>
#include"LeetCodeTools.hpp"

using namespace std;

class Solution {
public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        map<int, multiset<int>> mp;
        for (int i = 0; i < edges.size(); ++i)
        {
            mp[edges[i][0]].insert(edges[i][1]);
            mp[edges[i][1]].insert(edges[i][0]);

        }
        vector<int> hash(n + 1,0);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int times = mp[i].size() + mp[j].size() - mp[i].count(j);
                ++hash[times];
            }
        }
    }
};

int main() {
    int n = 4;
    vector<vector<int>> edges;
    wx::create("[[1,2],[2,4],[1,3],[2,3],[2,1]]", edges);
    vector<int> queries;
    wx::create("[2,3]", queries);
    Solution test;
    test.countPairs(n, edges, queries);
	return 0;
}