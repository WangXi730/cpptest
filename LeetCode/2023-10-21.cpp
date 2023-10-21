#include "LeetCodeTools.hpp"
leetcode

class Solution {
public:
    long long countPairs(int n, vector<vector<int>>& edges) {
        vector<list<int>> g(n);
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        vector<bool> visited(n, false);
        long long res = 0;
        for (int i = 0; i < n; ++i)
        {
            if(!visited[i]){
                visited[i] = true;
                int tmp = 0;
                dfs(tmp, i, visited, g);
                res += tmp * (n - tmp);
            }
        }
        return res / 2;
    }
private:
    void dfs(int& res, int i, vector<bool>& visited, vector<list<int>>& g) {
        ++res;
        for (auto& e : g[i]) {
            if (!visited[e]) {
                visited[e] = true;
                dfs(res, e, visited, g);
            }
        }
    }
};



int main() {
    Solution test;
    vector<vector<int>> arr;
    wx::create("[[65,0],[1,45],[57,2],[3,0],[46,4],[46,5],[46,6],[7,45],[1,9],[10,8],[50,11],[12,3],[8,13],[14,2],[6,15],[46,16],[17,12],[18,9],[19,8],[20,19],[50,21],[22,0],[3,23],[24,16],[15,25],[3,26],[27,3],[11,28],[29,25],[30,9],[20,31],[32,9],[33,9],[34,25],[11,35],[36,13],[37,4],[10,38],[45,39],[40,14],[26,41],[42,16],[43,24],[4,44],[31,47],[48,14],[49,40],[49,51],[52,31],[36,53],[54,35],[48,55],[56,33],[47,58],[59,54],[60,38],[12,61],[62,9],[57,63],[64,3],[35,66],[50,67],[33,68],[46,69],[70,21],[35,71],[12,72],[26,73],[50,74],[75,27],[26,76],[77,64],[33,78],[51,79],[80,68],[48,81],[82,75],[54,83],[63,84]]", arr);
    cout << test.countPairs(85, arr) << endl;
    return 0;
}