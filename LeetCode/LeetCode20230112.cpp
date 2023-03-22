#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>

using namespace std;

class Solution {
public:
    vector<string> findRepeatedDnaSequences(string s) {
        if (s.size() < 10) {
            return {};
        }
        unordered_map<string, int> hash;
        for (int i = 0; i <= s.size() - 10; ++i) {
            ++hash[s.substr(i, 10)];
        }
        vector<string> res;
        for (auto& e : hash) {
            if (e.second > 1) {
                res.push_back(e.first);
            }
        }
        return res;
    }
};

void rotate(vector<int>& nums, int k) {
    if (k > nums.size()) {
        k %= nums.size();
    }
    int n = nums.size();
    int* arr = new int[n];
    memcpy(arr, &nums[n - k], sizeof(int) * k);
    memcpy(arr + k, &nums[0], sizeof(int) * (n - k));
    memcpy(&nums[0], arr, sizeof(int) * n);
    delete[] arr;
}

int main() {
    vector<int> nums{ 1,2,3,4,5,6,7 };
    int k = 3;
    rotate(nums, k);
    return 0;
}