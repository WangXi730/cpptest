#include<iostream>
#include<string>
using namespace std;


class Solution {
public:
    int compareVersion(string version1, string version2) {
        int i = 0;
        int j = 0;
        int a = 0;
        int b = 0;
        while (i < version1.size() || j < version2.size()) {
            a = 0;
            b = 0;
            if (i < version1.size()) {
                int i1 = i;
                while (i1 < version1.size() && version1[i1] != '.') {
                    ++i1;
                }
                a = _string_to_integer(version1, i, i1);
                i = i1 + 1;
            }
            if (j < version2.size()) {
                int j1 = j;
                while (j1 < version2.size() && version2[j1] != '.') {
                    ++j1;
                }
                b = _string_to_integer(version2, j, j1);
                j = j1 + 1;
            }
            if (a < b) {
                return -1;
            }
            else if (a > b) {
                return 1;
            }
        }
        return 0;
    }
private:
    int _string_to_integer(string& s, int i, int j) {
        int res = 0;
        while (j > i) {
            res *= 10;
            res += s[i] - '0';
            i++;
        }
        return res;
    }
};


int main() {
    Solution test;
    test.compareVersion("1.0.1"
        , "1");
    return 0;
}