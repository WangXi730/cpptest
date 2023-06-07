#include<iostream>
#include<string>
using namespace std;
class Solution {
public:
    bool isValidSerialization(string preorder) {
        int st = 1;
        int i = 0;
        int n = preorder.size();
        for (i = 0; i < n; ++i) {
            if (preorder[i] == '#') {
                if (i < n)++i;
                --st;
            }
            else {
                while (i < n && preorder[i] != ',')++i;
                ++st;
            }
            if (st == 0) {
                break;
            }
        }
        return i == preorder.size() && st == 0;
    }
};

int main() {
    Solution test;
    test.isValidSerialization("9,3,4,#,#,1,#,#,2,#,6,#,#");
}