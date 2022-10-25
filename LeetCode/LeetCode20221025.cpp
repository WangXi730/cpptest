#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

class Solution {
public:
    bool isNumber(string s) {
        if (s[s.size() - 1] == 'e' || s[s.size() - 1] == 'E' || s == ".") {
            return false;
        }
        bool e = true;
        bool point = true;
        bool figer = false;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '+' || s[i] == '-') {
                if (i == 0) {
                    if (i == s.size() - 1 || (s[i + 1] < '0' || s[i + 1]>'9') && s[i + 1] != '.') {
                        return false;
                    }
                    continue;
                }
            }
            else if (s[i] == 'e' || s[i] == 'E') {
                if (e && figer) {
                    e = false;
                    if (i != s.size() - 1 && (s[i + 1] == '+' || s[i + 1] == '-')) {
                        ++i;
                    }
                    figer = false;
                    continue;
                }
            }
            else if (s[i] == '.') {
                if (point && e) {
                    if (figer == false && (i == s.size() - 1 || s[i + 1] > '9' || s[i + 1] < '0')) {
                        return false;
                    }
                    point = false;
                    continue;
                }
            }
            else if (s[i] >= '0' && s[i] <= '9') {
                figer = true;
                continue;
            }
            return false;
        }
        return figer ? true : false;
    }
    string addBinary(string a, string b) {
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        if (a.size() > b.size()) {
            b.resize(a.size(), '0');
        }
        else {
            a.resize(b.size(), '0');
        }
        for (int i = 0; i < a.size() - 1; ++i) {
            a[i] += b[i] - '0';
            if (a[i] > '1') {
                a[i] -= 2;
                a[i + 1] += 1;
            }
        }
        a[a.size() - 1] += b[b.size() - 1] - '0';
        if (a[a.size() - 1] > '1') {
            a[a.size() - 1] -= 2;
            a.push_back('1');
        }
        reverse(a.begin(), a.end());
        return a;
    }
};


int main() {
    Solution test;
    //test.isNumber("+.1");
    test.addBinary("1010", "1011");
    return 0;
}