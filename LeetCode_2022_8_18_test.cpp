#include<iostream>
using namespace std;


class Solution {
//剑指 Offer 67. 把字符串转换成整数
public:
    int strToInt(string str) {
        int i = 0;
        int f = 1;
        while (str[i] == ' ') {
            ++i;
        }
        if (str[i] == '+') {
            ++i;
        }
        else if (str[i] == '-') {
            ++i;
            f = -1;
        }
        else if (str[i] < '0' || str[i]>'9') {
            return 0;
        }

        int j = i;
        while (str[j] >= '0' && str[j] <= '9') {
            ++j;
        }
        while (str[i] == '0') {
            ++i;
        }
        string s(str.begin() + i, str.begin() + j);
        if (s.size() == 10) {
            if (f > 0) {
                if (s >= "2147483647") {
                    return 2147483647;
                }
            }
            else {
                if (s >= "2147483648") {
                    return -2147483648;
                }
            }
        }
        else if (s.size() > 10) {
            if (f > 0) {
                return 2147483647;
            }
            else {
                return -2147483648;
            }
        }
        int res = 0;
        while (i < j) {
            res = res * 10 + (str[i] - '0');
            ++i;
        }
        return res * f;
    }
};

int main() {
    Solution a;
    a.strToInt("20000000000000000000");
	return 0;
}