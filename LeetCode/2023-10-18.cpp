#include"LeetCodeTools.hpp"
//using namespace std;
//using namespace wx;

leetcode

class Solution {
public:
    long long maxKelements(vector<int>& nums, int k) {
        long long res = 0;
        priority_queue<int> q;
        for (int i = 0; i < nums.size(); ++i) {
            q.push(nums[i]);
        }
        while (k--) {
            int tmp = q.top();
            q.pop();
            res += tmp;
            if (tmp / 3 * 3 == tmp) {
                q.push(tmp / 3);
            }
            else {
                q.push(tmp / 3 + 1);
            }
        }
        return res;
    }
public:
        int sumOfMultiples(int n) {
            int res = 0;
            for (int i = 0; i <= n; ++i) {
                if (i % 3 == 0 || i % 5 == 0 || i % 7 == 0) {
                    res += i;
                }
            }
            return res;
        }
    
};

int main() {
    vector<int> arr{ 10,10,10,10,10 };
    Solution test;
    cout << test.maxKelements(arr, 5) << endl;
    cout << test.sumOfMultiples(7);
    return 0;
}