#include<iostream>
#include<vector>
#include<string>

using namespace std;
class Solution {
public:
    vector<bool> canMakePaliQueries(string s, vector<vector<int>>& queries) {
        int s_size = s.size();
        int q_size = queries.size();
        vector<bool> res(q_size, false);
        for (int i = 0; i < q_size; ++i) {
            int arr[26] = { 0 };
            for (int j = queries[i][0]; j <= queries[i][1]; ++j) {
                ++arr[s[j] - 'a'];
            }
            int error = 0;
            for (int j = 0; j < 26; ++j) {
                if (arr[j] % 2 != 0) {
                    ++error;
                }
            }
            if (error / 2 <= queries[i][2]) {
                res[i] = true;
            }
        }
        return res;
    }
};

#include"LeetCode_array.hpp"
int main() {
    Solution test;
    //string s = "[[3,3,0],[1,2,0],[0,3,1],[0,3,2],[0,4,1]]";
    //wx::array_to_c(s);
    vector<vector<int>> arr{ {3, 3, 0}, { 1,2,0 }, { 0,3,1 }, { 0,3,2 }, { 0,4,1 } };
    test.canMakePaliQueries("abcda", arr);
    //cout << s;
    return 0;
}


