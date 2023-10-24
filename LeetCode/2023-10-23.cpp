#include<iostream>
#include"LeetCodeTools.hpp"

leetcode
class Solution {
public:
    vector<int> avoidFlood(vector<int>& rains) {
        int n = rains.size();
        unordered_map<int, int> ump;//水池 ： 满的日期
        ump.reserve(n);
        set<int> st;//可以用来赈灾的天
        vector<int> ans(n, 0);
        for (int i = 0; i < n; ++i) {
            if (rains[i] != 0) {
                ans[i] = -1;
                if (ump.find(rains[i]) == ump.end()) {
                    //注水
                    ump[rains[i]] = i;
                }
                else {
                    //赈灾
                    auto it = st.lower_bound(ump[rains[i]]);
                    if (it == st.end()) {
                        //赈灾失败
                        return {};
                    }
                    if (*it < i) {
                        //赈灾成功
                        ans[*it] = rains[i];
                        st.erase(it);
                        ump[rains[i]] = i;
                    }
                    else {
                        //赈灾失败
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