#include<iostream>
#include<unordered_map>
#include<string>
#include<vector>
#include<sstream>
#include<map>
using namespace std;
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        string res;
        map<int, int> hash;
        if (numerator / denominator > 10) {
            stringstream ss;
            ss << numerator / denominator;
            ss >> res;
        }
        else
            res.push_back(numerator / denominator + '0');
        int mod = numerator % denominator;
        int i = 1;
        bool point = false;
        while (mod != 0) {
            while (mod < denominator) {
                if (point) {
                    res.push_back('0');
                    if (hash.find(mod) == hash.end()) {
                        hash[mod] = i;
                    }
                }
                else {
                    res.push_back('.');
                    point = true;
                }
                mod *= 10;
                ++i;
            }
            //判断循环小数
            //被除数变mod
            numerator = mod;
            mod = numerator % denominator;
            pair<int, int> p = {mod,i };
            //循环体首先得在小数部分
            res.push_back(numerator / denominator + '0');
            if (point) {
                if (hash.find(p.first) != hash.end()) {
                    //出现循环体
                    int j = 0;
                    int idx = hash[p.first];
                    while (*(res.rbegin()) == res[idx - j]) {
                        res.pop_back();
                        ++j;
                    }
                    string tmp = res.substr(idx - j + 1);
                    res.resize(idx - j + 1);
                    res += "(" + tmp + ")";
                    return res;
                }
                else {
                    hash.insert(p);
                }
            }
            ++i;
            mod *= 10;
        }
        return res;
    }
};


int main() {
    Solution test;
    test.fractionToDecimal(2147483647, 37);
    return 0;
}