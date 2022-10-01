#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        //排序
        sort(nums.begin(), nums.end());
        //创建返回值
        vector<vector<int>> res;
        if (nums[0] > 0 || nums[nums.size() - 1] < 0) {
            return res;
        }
        for (int i = 0; i < nums.size() - 2; ++i) {
            if (i != 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            int j = i + 1;
            int k = nums.size() - 1;
            while (j < k) {
                int tmp = nums[i] + nums[j] + nums[k];
                if (tmp == 0) {
                    res.push_back({ nums[i],nums[j],nums[k] });
                    ++j;
                    --k;
                }
                else if (tmp > 0) {
                    --k;
                }
                else {
                    ++j;
                }
                while (j < k && nums[j] == nums[j - 1])++j;
                while (j < k && nums[k] == nums[k + 1])--k;
            }
        }
        return res;
    }
    public:
        int threeSumClosest(vector<int>& nums, int target) {
            sort(nums.begin(), nums.end());
            int res = nums[0] + nums[1] + nums[2];
            //枚举第一个变量
            for (int i = 0; i < nums.size() - 2; ++i) {
                int left = i + 1;
                int right = nums.size() - 1;
                while (left < right) {
                    //判断当前是否比res小
                    int tmp = nums[i] + nums[right] + nums[left];
                    if (abs(res - target) > abs(tmp - target)) {
                        res = tmp;
                    }
                    //进行移动
                    if (tmp < target) {
                        ++left;
                    }
                    else if (tmp > target) {
                        --right;
                    }
                    else {
                        return target;
                    }
                }
            }
            return res;
        }
};


int main() {
    Solution a;
    //vector<int>  t = { -2, 0, 1, 1, 2};
    //a.threeSum(t);
    vector<int> t = {4, 0, 5, -5, 3, 3, 0, -4, -5};
    a.threeSumClosest(t, -2);
    return 0;
}