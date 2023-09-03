#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution {
public:
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        vector<float> time(dist.size());
        for (int i = 0; i < time.size(); ++i) {
            time[i] = dist[i] / (float)speed[i];
        }
        sort(time.begin(), time.end());
        for (int i = 0; i < time.size(); ++i) {
            if (i >= time[i]) {
                return i;
            }
        }
        return time.size();
    }
    int captureForts(vector<int>& forts) {
        int res = 0;
        for (int i = 0; i < forts.size();) {
            if (forts[i]) {
                int t = i;
                while (++i < forts.size() && forts[i] == 0);
                if (i < forts.size() && forts[i] * forts[t] == -1) {
                    res = max(res, i - t - 1);
                }
            }
            else {
                ++i;
            }

        }
        return res;
    }
};

#include"LeetCode_array.hpp"
int main() {
    Solution test;
    vector<int> arr { 1, 0, 0, -1, 0, 0, 0, 0, 1};
    cout << test.captureForts(arr);
}
