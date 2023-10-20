#include"LeetCodeTools.hpp"
leetcode

#include<thread>
#include<memory>
class Solution {
public:
    double frogPosition(int n, vector<vector<int>>& edges, int t, int target) {
        unordered_map<int, unordered_set<int>> link;
        vector<bool> trace(n + 1, false);
        for (int i = 0; i < edges.size(); ++i) {
            link[edges[i][0]].insert(edges[i][1]);
            link[edges[i][1]].insert(edges[i][0]);
        }
        stack<data> st;
        st.push(data(0,1,1));
        trace[1] = true;
        while (!st.empty()) {
            auto node = st.top();
            st.pop();
            int count = 0;
            for (auto& e : link[node.value]) {
                if (trace[e]) {
                    continue;
                }
                ++count;
            }
            if (node.value == target) {
                if(node.time == t || count == 0)
                    return node.chance;
                else {
                    break;
                }
            }
            if (node.time == t) {
                continue;
            }
            for (auto& e : link[node.value]) {
                if (trace[e]) {
                    continue;
                }
                trace[e] = true;
                st.push(data(node.time + 1,e,node.chance / count));
            }
        }
        return 0;
    }
private:
    struct data
    {
        data(int t, int v, double c):time(t),value(v),chance(c){}
        int time = 0;
        int value = 0;
        double chance = 0;
    };
public:
    string oddString(vector<string>& words) {
        vector<int> difference(words[0].size() - 1);
        //记录第一个字符串
        for (int i = 0; i < words[0].size() - 1; ++i) {
            difference[i] = words[0][i + 1] - words[0][i];
        }
        int diff_index = 0;
        bool find_eq = false;
        for (int i = 1; i < words.size(); ++i) {
            bool eq = true;
            for (int j = 0; j < words[i].size() - 1; ++j) {
                if (difference[j] == words[i][j + 1] - words[i][j]) {
                    continue;
                }
                eq = false;
                break;
            }
            if (eq) {
                if (diff_index != 0) {
                    return words[diff_index];
                }
                find_eq = eq;
            }
            else {
                if (find_eq) {
                    return words[i];
                }
                else if (diff_index == 0) {
                    diff_index = i;
                }
                else {
                    break;
                }
            }
        }
        return words[0];
    }
public:
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        if (grid[0][0] != 0 || grid[grid.size() - 1][grid[0].size() - 1] != 0) {
            return -1;
        }
        else if (grid.size() == 1 && grid[0].size() == 1) {
            return 1;
        }
        //使用bfs
        queue<pair<int,int>> q;
        q.push(make_pair(0, 0));
        grid[0][0] = 1;
        int i = 1;
        while (!q.empty()) {
            queue<pair<int, int>> tmp_q;
            bool find_node = false;
            while (!q.empty()) {
                pair<int, int> node = q.front();
                q.pop();
                if (node.first + 1 == grid.size() && node.second + 1 == grid[0].size()) {
                    find_node = true;
                    break;
                }
                if (node.first + 1 < grid.size() && node.second + 1 < grid.size() && grid[node.first + 1][node.second + 1] == 0) {
                    grid[node.first + 1][node.second + 1] = 1;
                    tmp_q.push(make_pair(node.first + 1, node.second + 1));
                }
                if (node.second + 1 < grid.size() && grid[node.first][node.second + 1] == 0) {
                    grid[node.first][node.second + 1] = 1;
                    tmp_q.push(make_pair(node.first, node.second + 1));
                }
                if (node.first + 1 < grid.size() && grid[node.first + 1][node.second] == 0) {
                    grid[node.first + 1][node.second] = 1;
                    tmp_q.push(make_pair(node.first + 1, node.second));
                }
                if (node.first - 1 >= 0 && grid[node.first - 1][node.second] == 0) {
                    grid[node.first - 1][node.second] = 1;
                    tmp_q.push(make_pair(node.first - 1, node.second));
                }
                if (node.second - 1 >=0 && grid[node.first][node.second - 1] == 0) {
                    grid[node.first][node.second - 1] = 1;
                    tmp_q.push(make_pair(node.first, node.second - 1));
                }
                if (node.first - 1 < grid.size() && node.second - 1 < grid.size() && grid[node.first - 1][node.second - 1] == 0) {
                    grid[node.first - 1][node.second - 1] = 1;
                    tmp_q.push(make_pair(node.first - 1, node.second - 1));
                }
                if (node.first + 1 < grid.size() && node.second - 1 < grid.size() && grid[node.first + 1][node.second - 1] == 0) {
                    grid[node.first + 1][node.second - 1] = 1;
                    tmp_q.push(make_pair(node.first + 1, node.second - 1));
                }
                if (node.first - 1 < grid.size() && node.second + 1 < grid.size() && grid[node.first - 1][node.second + 1] == 0) {
                    grid[node.first - 1][node.second + 1] = 1;
                    tmp_q.push(make_pair(node.first - 1, node.second + 1));
                }

            }
            if (find_node) {
                return i;
            }
            ++i;
            q.swap(tmp_q);
        }
        return -1;
    }
    public:
        vector<double> sampleStats(vector<int>& count) {
            double mean = 0;
            int minimum = -1;
            int maximum = -1;
            int mode = -1;
            int allcount = 0;
            for (int i = 0; i < count.size(); ++i) {
                if (minimum == -1 && count[i] > 0) {
                    minimum = i;
                }
                if (count[i] > 0) {
                    maximum = i;
                    if (mode == -1 || count[mode] < count[i]) {
                        mode = i;
                    }
                }
                mean += count[i] * i;
                allcount += count[i];
            }
            mean /= allcount;
            int mid1 = allcount / 2 + 1;
            int mid2 = allcount % 2 == 0 ? mid1 - 1 : mid1;
            double median1 = -1;
            double median2 = -1;
            int c = 0;
            for (int i = 0; i < count.size(); ++i) {
                if (mid1 > c && mid1 <= c + count[i]) {
                    median1 = i;
                }
                if (mid2 > c && mid2 <= c + count[i]) {
                    median2 = i;
                }
                if (median1 != -1 && median2 != -1) {
                    break;
                }
                c += count[i];
            }
            vector<double> res{ (double)minimum,(double)maximum,mean,(median1 + median2) / 2,(double)mode };
            return res;
        }
    public:
        int kthSmallest(vector<vector<int>>& mat, int k) {
            vector<int> arr;
            dfs(arr, mat,0,0);
            nth_element(arr.begin(), arr.begin() + k - 1, arr.end(), std::less<int>());
            return arr[k - 1];
        }
private:
    void dfs(vector<int>& arr, vector<vector<int>>& mat, int t, int i) {
        if (i == mat.size()) {
            arr.push_back(t);
            return;
        }
        for (int j = 0; j < mat[i].size(); ++j) {
            dfs(arr, mat, t + mat[i][j], i + 1);
        }
    }
};

int main() {
    Solution test;
    vector<vector<int>> edges;
    wx::create("[[2,1],[3,2],[4,1],[5,1],[6,4],[7,1],[8,7]]", edges);
    cout << test.frogPosition(8,edges, 7, 7) << endl;
    vector<string> words;
    wx::create(R"(["zaaaaaaaaaaaaaaaaaaa","yaaaaaaaaaaaaaaaaaaa","zaaaaaaaaaaaaaaaaaaa"])", words);
    cout << test.oddString(words) << endl;
    vector<vector<int>> arr;
    wx::create("[[0,1,1,0,0,0],[0,1,0,1,1,0],[0,1,1,0,1,0],[0,0,0,1,1,0],[1,1,1,1,1,0],[1,1,1,1,1,0]]", arr);
    cout << test.shortestPathBinaryMatrix(arr) << endl;
    vector<int> a{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
    test.sampleStats(a);
    vector<vector<int>> mat;
    wx::create("[[1,3,11],[2,4,6]]", mat);
    test.kthSmallest(mat, 5);
	return 0;
}