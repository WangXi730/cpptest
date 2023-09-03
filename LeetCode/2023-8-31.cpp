#include<iostream>
#include<set>
#include<map>
#include<vector>
#include<unordered_map>
#include"LeetCode_array.hpp"

using namespace std;

class Solution {
public:
    int minTrioDegree(int n, vector<vector<int>>& edges) {
        //1、先找到所有的三元组
        //1.1、找到所有的元素的度
        //unordered_map<int, set<int>> mp;
        vector<vector<bool>> mp(n + 1,vector<bool>(n + 1,false));
        vector<int> count(n + 1, 0);
        for (int i = 0; i < edges.size(); ++i) {
            //mp[edges[i][0]].insert(edges[i][1]);
            //mp[edges[i][1]].insert(edges[i][0]);
            mp[edges[i][0]][edges[i][1]] = mp[edges[i][1]][edges[i][0]] = true;
            ++count[edges[i][0]];
            ++count[edges[i][1]];
        }
        //1.2、找到所有的三元组
        //set<set<int>> three;
        /*for (auto& e : mp) {
            if (e.second.size() >= 2) {
                for (auto& t1 : e.second) {
                    for (auto& t2 : e.second) {
                        if (t1 == t2) {
                            continue;
                        }
                        if (mp[t1].find(t2) != mp[t1].end() && mp[t2].find(t1) != mp[t2].end()) {
                            set<int> tmp;
                            tmp.insert(t1);
                            tmp.insert(t2);
                            tmp.insert(e.first);
                            three.insert(move(tmp));
                        }
                    }
                }
            }
        }*/
        //2、计算它们的度，记录并返回最小值
        int res = -1;
        //for (auto& e : three) {
        //    int tmp = 0;
        //    for (auto& t : e) {
        //        tmp += mp[t].size();
        //    }
        //    if (tmp < res || res == -1) {
        //        res = tmp;
        //    }
        //}
        for (int i = 1; i < n; ++i) {
            if (count[i] >= 2) {
                for (int j = i + 1; j < n; ++j) {
                    if (mp[i][j] == false) {
                        continue;
                    }
                    for (int k = j + 1; k <= n; ++k) {
                        if (mp[j][k] == true && mp[i][k] == true) {
                            int tmp = count[i] + count[j] + count[k];
                            if (res > tmp || res == -1) {
                                res = tmp;
                            }
                        }
                    }
                }
            }
        }


        return res < 0 ? -1 : res - 6;
    }
};


int main() {
    //string s = "[[1,3],[4,1],[4,3],[2,5],[5,6],[6,7],[7,5],[2,6]]";
    //wx::array_to_c(s);
    //cout << s;
    vector<vector<int>> v {{1, 2}, { 1,3 }, { 3,2 }, { 4,1 }, { 5,2 }, { 3,6 }};
    Solution test;
    std::cout << test.minTrioDegree(6,v) << std::endl;
    vector<vector<int>> v2{{1, 3}, { 4,1 }, { 4,3 }, { 2,5 }, { 5,6 }, { 6,7 }, { 7,5 }, { 2,6 }};
    std::cout << test.minTrioDegree(7, v2) << std::endl;
    vector<vector<int>> v3{{1, 2}, { 4,1 }, { 4,2 }};
    std::cout << test.minTrioDegree(4, v3) << std::endl;
    return 0;
}

