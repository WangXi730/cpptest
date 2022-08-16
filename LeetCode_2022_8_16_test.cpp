#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
    //leetcode剑指61
    bool isStraight(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int sum0 = 0;
        while (sum0 < nums.size() && nums[sum0++] == 0);
        int i = --sum0;
        while (i < nums.size() - 1) {
            if (nums[i + 1] == nums[i] + 1) {
                ++i;
            }
            else if (nums[i + 1] == nums[i]) {
                return false;
            }
            else if (sum0 != 0) {
                --sum0;
                ++nums[i];
            }
            else {
                return false;
            }
        }
        return true;
    }
    //剑指 Offer 62. 圆圈中最后剩下的数字
    int lastRemaining(int n, int m) {
     
    }
};
int main() {
    Solution a;
    /*
    vector<int> test_isStraight{0,0,2,2,5};
    a.isStraight(test_isStraight);
    */
    a.lastRemaining(5, 3);
    return 0;

}