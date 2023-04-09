#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include<unordered_set>
using namespace std;



class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        map<int, int> h2r_m;//height_to_right_map
        map<int, char> change_point;//���ܳ��ָ߶�ͻ��ĵ㣬1������2�����ң�1|2��������
        map<int, int> l2r_m;//left_to_right_map
        map<int, int> l2h_m;//left_to_hight_map
        vector<vector<int>> res;
        //map init
        for (int i = 0; i < buildings.size(); ++i) {
            if (i < buildings.size()-1 && buildings[i][0] == buildings[i + 1][0]) {
                int j = i;
                for (j = i; j < buildings.size() - 1; ++j) {
                    if (buildings[j][0] != buildings[j + 1][0]) {
                        break;
                    }
                }
                //��ô������ȷ�����ǣ���i��j��leftlim��ͬ��
                for (int k = i; k <= j; ++k) {
                    //ͬ�߶�ѡ�����Ҳ��Ϊ׼
                    h2r_m[buildings[k][2]] = max(buildings[k][1],h2r_m[buildings[k][2]]);
                }
                int k = buildings[i][0];
                //����ѡȡ��ߵģ������k��һ��left�Ľ�ɫ
                while (!h2r_m.empty()) {
                    auto e = h2r_m.rbegin();
                    if (e->second > k) {
                        l2r_m[k] = e->second;
                        l2h_m[k] = e->first;
                        change_point[k] |= 1;
                        k = e->second;
                        change_point[k] |= 2;
                    }
                    h2r_m.erase(e->first);
                }
                //change_point[k] += 2;
                i = j;
                continue;
            }

            l2r_m[buildings[i][0]] = buildings[i][1];
            l2h_m[buildings[i][0]] = buildings[i][2];
            change_point[buildings[i][0]] |= 1;
            change_point[buildings[i][1]] |= 2;
        }

        //step
        for (auto& e : change_point) {
            //ͳ�Ƹı�ǰ����ߵ�
            int h = 0;
            if (!h2r_m.empty()) {
                h = h2r_m.rbegin()->first;
            }
            //��ʼ�ı�
            if (e.second & 1) {
                //leftlim
                //����
                //���������ͬ�ģ���ôȡʱ�����Զ������
                h2r_m[l2h_m[e.first]] = max(l2r_m[e.first], h2r_m[l2h_m[e.first]]);
            }
            //����h2r_m
            while (!h2r_m.empty() && e.first >= h2r_m.rbegin()->second) {
                h2r_m.erase(h2r_m.rbegin()->first);
            }
            if (h2r_m.empty()) {
                if (h != 0) {
                    res.push_back({ e.first,0 });
                }
            }
            else {
                if (h != h2r_m.rbegin()->first) {
                    res.push_back({ e.first,h2r_m.rbegin()->first });
                }
            }
        }

        return res;
    }
};

#include"C:\git\cpptest\LeetCode\LeetCode_array.hpp"

int main() {
    Solution test;
    vector<vector<int>> a{ {1,38,219},{2,19,228},{2,64,106},{3,80,65},{3,84,8},{4,12,8},{4,25,14},{4,46,225},{4,67,187},{5,36,118},{5,48,211},{5,55,97},{6,42,92},{6,56,188},{7,37,42},{7,49,78},{7,84,163},{8,44,212},{9,42,125},{9,85,200},{9,100,74},{10,13,58},{11,30,179},{12,32,215},{12,33,161},{12,61,198},{13,38,48},{13,65,222},{14,22,1},{15,70,222},{16,19,196},{16,24,142},{16,25,176},{16,57,114},{18,45,1},{19,79,149},{20,33,53},{21,29,41},{23,77,43},{24,41,75},{24,94,20},{27,63,2},{31,69,58},{31,88,123},{31,88,146},{33,61,27},{35,62,190},{35,81,116},{37,97,81},{38,78,99},{39,51,125},{39,98,144},{40,95,4},{45,89,229},{47,49,10},{47,99,152},{48,67,69},{48,72,1},{49,73,204},{49,77,117},{50,61,174},{50,76,147},{52,64,4},{52,89,84},{54,70,201},{57,76,47},{58,61,215},{58,98,57},{61,95,190},{66,71,34},{66,99,53},{67,74,9},{68,97,175},{70,88,131},{74,77,155},{74,99,145},{76,88,26},{82,87,40},{83,84,132},{88,99,99} };
    test.getSkyline(a);
    return 0;
}