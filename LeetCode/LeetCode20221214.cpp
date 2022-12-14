#include<iostream>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
class Solution {
public:
    int maximumGap(vector<int>& nums) {
        if (nums.size() <= 1) {
            return 0;
        }
        //这里使用桶的方法
        int inf = *min_element(nums.begin(), nums.end());
        int sup = *max_element(nums.begin(), nums.end());
        int d = (sup - inf) / (nums.size() - 1);
        d = max(1, d);
        vector<pair<int, int>> bucket((sup - inf) / d + 1, { -1,-1 });
        //维护每个区间的最大值和最小值
        for (int i = 0; i < nums.size(); ++i) {
            int idx = (nums[i] - inf) / d;
            if (bucket[idx].first == -1) {
                bucket[idx].first = bucket[idx].second = nums[i];
            }
            else {
                bucket[idx].first = min(bucket[idx].first, nums[i]);
                bucket[idx].second = max(bucket[idx].second, nums[i]);
            }
        }
        //寻找返回值
        int res = 0;
        for (int i = 0; i < bucket.size() - 1;) {
            int j = i + 1;
            for (; j < bucket.size(); ++j) {
                if (bucket[j].first != -1) {
                    break;
                }
            }
            if (res < bucket[j].first - bucket[i].second) {
                res = bucket[j].first - bucket[i].second;
            }
            i = j;
        }
        return res;
    }
};

int main() {
    vector<int> nums{ 1,10000 };
    Solution test;
    cout << test.maximumGap(nums);
    return 0;
}