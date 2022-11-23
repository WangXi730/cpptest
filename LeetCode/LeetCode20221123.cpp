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
            //ֱ��x = e.first�ϵĵ�
            if (e.second.size() > res) {
                res = e.second.size();
            }
            //������
            for (int i = 0; i < e.second.size(); ++i) {
                for (auto& e2 : hash) {
                    //����б��
                    int dx = e2.first - e.first;//б�ʷ�ĸ
                    if (e2.first <= e.first) {
                        continue;
                    }
                    for (int j = 0; j < e2.second.size(); ++j) {
                        int dy = e2.second[j] - e.second[i];//б�ʷ���
                        //��������ÿһ��x���м��
                        int _mod = dy % dx;
                        int tmp_res = 2;
                        for (auto& e3 : hash) {
                            if (e3.first <= e2.first) {
                                continue;
                            }
                            else if (_mod * (e3.first - e2.first) % dx != 0) {
                                //����x��yֻ������������ô���۲����x���������϶�Ӧ��y�ǲ���������������ǣ���û��Ҫ����
                                continue;
                            }
                            //�����x��Ӧ��y���м���
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