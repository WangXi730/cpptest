#include<iostream>
#include<string>
#include<vector>
#include<sstream>
using namespace std;
class Solution {
public:
    string fractionAddition(string expression) {
        vector<int> figure;
        my_split(figure, expression);
        long long fenmu = 1;
        for (int i = 1; i < figure.size(); i += 2) {
            fenmu *= figure[i];
        }
        long long fenzi = 0;
        for (int i = 0; i < figure.size(); i += 2) {
            fenzi += figure[i] * fenmu / figure[i + 1];
        }
        if (fenzi == 0) {
            fenmu = 1;
        }
        else {
            //约分
            //1、求最大公约数
            int t = common_divisor(fenzi,fenmu);
            //2、约分
            fenzi /= t;
            fenmu /= t;
        }
        if (fenmu < 0) {
            fenmu *= -1;
            fenzi *= -1;
        }
        stringstream ss;
        ss << fenzi << "/" << fenmu;
        return ss.str();
    }
private:
    void my_split(vector<int>& figure, string& expression) {
        int tmp = 0;
        int j = 0;
        figure.resize(20);
        int i = 0;
        int sig = 1;
        if (expression[i] == '-') {
            sig = -1;
            ++i;
        }
        for (; i < expression.size(); ++i) {
            switch (expression[i]) {
            case '/': figure[j++] = tmp * sig; tmp = 0; break;
            case '+': figure[j++] = tmp; sig = 1; tmp = 0; break;
            case '-': figure[j++] = tmp; sig = -1; tmp = 0; break;
            default:tmp *= 10; tmp += (expression[i] - '0');
            }
        }
        figure[j++] = tmp;
        figure.resize(j);
    }
    int common_divisor(int a, int b) {
        if (a < 0) {
            a = -a;
        }
        if (b < 0) {
            b = -b;
        }
        if (a > b) {
            int tmp = a;
            a = b;
            b = tmp;
        }
        if (b % a == 0) {
            return a;
        }
        int res = 1;
        int tmp = 2;
        while (tmp < a/2) {
            if (a % tmp == 0 && b % tmp == 0) {
                res *= tmp;
                a /= tmp;
                b /= tmp;
                tmp = 2;
            }
            else {
                ++tmp;
            }
        }
        return res;
    }
};


int main() {
    Solution test;
    cout << test.fractionAddition("4/1+6/5-1/8-9/2-1/1+6/7-10/7-3/4-3/2-1/1");
    return 0;
}