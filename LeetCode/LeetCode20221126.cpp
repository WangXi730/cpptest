#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        while (left < right - 1) {
            int mid = (left + right) / 2;
            if (nums[mid] < nums[left]) {
                right = mid;
            }
            else if (nums[mid] > nums[right]) {
                left = mid;
            }
            else {
                return nums[left];
            }
        }
        return min(nums[left],nums[right]);
    }
};


int main(){
    vector<int> a{ 3,4,5,1,2 };
    Solution test;
    test.findMin(a);
    return 0;
}