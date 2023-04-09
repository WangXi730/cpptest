#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
using namespace std;
class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int indexDiff, int valueDiff) {
        multimap<int, int> rbt;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = rbt.insert(make_pair(nums[i], i));
            map<int, int>::reverse_iterator rit(it);
            ++it;
            ++rit;
            while (it != rbt.end()) {
                if (i - it->second > indexDiff) {
                    rbt.erase(it++);
                }
                else if (it->first - nums[i] <= valueDiff) {
                    return true;
                }
                else {
                    break;
                }
            }
            while (rit != map<int,int>::reverse_iterator(rbt.end())) {
                if (i - (rit.base()->second) > indexDiff) {
                    rbt.erase((rit++).base());
                }
                else if (nums[i] - rit.base()->first <= valueDiff) {
                    return true;
                }
                else {
                    break;
                }
            }
        }
        return false;
    }
};



int main() {
    Solution test;
    vector<int> nums = { 1,5,9,1,5,9};
    
    if (test.containsNearbyAlmostDuplicate(nums, 2, 3)) {
        std::cout << "true";
    }
    else {
        std::cout << "false";
    }
    return 0;
}