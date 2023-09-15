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
        vector<int> hash(edges.size() + 1, 0);
        for (int i = 1; i <= n; ++i) {
            for (int j = i + 1; j <= n; ++j) {
                int times = mp[i].size() + mp[j].size() - mp[i].count(j);
                ++hash[times];
            }
        }
        for (int i = hash.size() - 2; i >= 0; --i) {
            hash[i] += hash[i + 1];
        }
        vector<int> res(queries.size());
        for (int i = 0; i < queries.size(); ++i) {
            res[i] = hash[queries[i] + 1];
        }
        return res;
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