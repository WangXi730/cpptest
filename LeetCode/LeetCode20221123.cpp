#include<iostream>
#include<vector>
#include<map>

using namespace std;

class Solution {
public:
    int maxPoints(vector<vector<int>>& points) {
        map<int, vector<int>> hash;
        for (int i = 0; i < points.size(); ++i) {
            hash[points[i][0]].push_back(points[i][1]);
        }
        int res = 0;
        for (auto& e : hash) {
            //直线x = e.first上的点
            if (e.second.size() > res) {
                res = e.second.size();
            }
            //其他点
            for (int i = 0; i < e.second.size(); ++i) {
                for (auto& e2 : hash) {
                    //计算斜率
                    int dx = e2.first - e.first;//斜率分母
                    if (e2.first <= e.first) {
                        continue;
                    }
                    for (int j = 0; j < e2.second.size(); ++j) {
                        int dy = e2.second[j] - e.second[i];//斜率分子
                        //接下来对每一个x进行检测
                        int _mod = dy % dx;
                        int tmp_res = 2;
                        for (auto& e3 : hash) {
                            if (e3.first <= e2.first) {
                                continue;
                            }
                            else if (_mod * (e3.first - e2.first) % dx != 0) {
                                //由于x、y只能是整数，那么，观察这个x在这条线上对应的y是不是整数，如果不是，就没必要算了
                                continue;
                            }
                            //对这个x对应的y进行计算
                            int dy2 = _mod * (e3.first - e2.first) / dx + dy / dx * (e3.first - e2.first);
                            int y = e2.second[j] + dy2;
                            for (int k = 0; k < e3.second.size(); ++k) {
                                if (y == e3.second[k]) {
                                    ++tmp_res;
                                    break;
                                }
                            }
                        }
                        if (tmp_res > res) {
                            res = tmp_res;
                        }
                    }
                }
            }
        }
        return res;
    }
};


int main() {
    Solution test;
    vector<vector<int>> v{ {1,1},{1,4},{2,3},{3,2 },{4,1},{5,3} };
    test.maxPoints(v);
    return 0;
}