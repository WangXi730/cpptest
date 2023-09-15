#include<iostream>
#include"LeetCodeTools.hpp"

using namespace std;

class Solution {
public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        vector<int> link(edges.size(), 1);
        for (int i = 0; i < edges.size(); ++i) {
            for (int j = i + 1; j < edges.size(); ++j) {
                if (edges[i][0] == edges[j][0] || edges[i][0] == edges[j][1] || edges[i][1] == edges[j][0] || edges[i][1] == edges[j][1]) {
                    ++link[i];
                    ++link[j];
                }
            }
        }
        vector<int> hash(edges.size() + 1, 0);
        for (int i = 0; i < hash.size(); ++i) {
            ++hash[link[i]];
        }
        for (int i = 1; i < hash.size(); ++i) {
            hash[i] += hash[i - 1];
        }
        vector<int> answers(queries.size(), 0);
        for (int i = 0; i < queries.size(); ++i) {
            answers[i] = hash[queries[i]];
        }
        return answers;
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