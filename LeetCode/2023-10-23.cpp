#include<iostream>
#include"LeetCodeTools.hpp"

leetcode
class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        unordered_map<int, int> ump;//ˮ�� �� ��������
        ump.reserve(n);
        set<int> st;//�����������ֵ���
        vector<int> ans(n, 0);
        for (int i = 0; i < n; ++i) {
            if (rains[i] != 0) {
                ans[i] = -1;
                if (ump.find(rains[i]) == ump.end()) {
                    //עˮ
                    ump[rains[i]] = i;
                }
                else {
                    //����
                    auto it = st.lower_bound(ump[rains[i]]);
                    if (it == st.end()) {
                        //����ʧ��
                        return {};
                    }
                    if (*it < i) {
                        //���ֳɹ�
                        ans[*it] = rains[i];
                        st.erase(it);
                        ump[rains[i]] = i;
                    }
                    else {
                        //����ʧ��
                        return {};
                    }
                }
            }
            else {
                st.insert(i);
            }
        }
        for (auto& e : st) {
            ans[e] = 1;
        }
        return ans;
    }

};


int main() {
    Solution test;
    vector<int> rains{ 1,2,0,1,2};
    test.avoidFlood(rains);
	return 0;
}