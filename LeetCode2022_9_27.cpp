#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Solution {
public:
    int longestValidParentheses(string s) {
        if (s.size() == 0) {
            return 0;
        }
        int max_count = 0;
        //使用二叉平衡树的方式
        int balance = 0;
        int beg = 0;
        int beg_count = 0;
        bool beg_ing = true;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                --balance;
                if (beg_ing) {
                    ++beg_count;
                }
            }
            else if (s[i] == ')') {
                ++balance;
                beg_ing = false;
                if (balance > 0) {
                    beg = i + 1;
                    balance = 0;
                    beg_ing = true;
                    beg_count = 0;
                    continue;
                }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             if (balance + beg_count > 0) {
                    if (i - beg + balance + 1 > max_count) {
                        max_count = i - beg + balance + 1;
                    }
                    if (balance == 0) {
                        beg_ing = true;
                        beg_count = 0;
                    }
                }
            }
        
        }
        return max_count;
    }
    bool isMatch(string s, string p) {
        //补丁处理空字符串匹配提高效率
        if (s == p) {
            return true;
        }
        else if (p.size() == 0 && s.size() != 0) {
            return false;
        }
        // v[i][j] 用来存放 s 的前 i 个字符是否与 p 的前 j 个字符匹配
        vector<vector<bool>> v(s.size() + 1, vector<bool>(p.size() + 1, false));
        //俩空字符串匹配结果是true
        v[0][0] = true;
        for (int i = 2; i <= p.size(); i += 2) {
            if (p[i - 1] == '*')
                v[0][i] = v[0][i - 2];
        }
        //p的一个字符匹配s的多个字符一定会失败，这与初始化的结果相同，所以不做讨论
        //接下来从两个字符开始匹配，i表示s的字符个数，j表示p的字符个数
        for (int i = 1; i <= s.size(); ++i) {
            for (int j = 1; j <= p.size(); ++j) {
                //匹配
                if (p[j - 1] == '.' || p[j - 1] == s[i - 1]) {
                    v[i][j] = v[i - 1][j - 1];
                }
                else if (p[j - 1] == '*') {
                    if (p[j - 2] == '.' || p[j - 2] == s[i - 1]) {
                        v[i][j] = v[i][j - 2] || v[i - 1][j];
                    }
                    else {
                        v[i][j] = v[i][j - 2];
                    }
                }
            }
        }
        return v[v.size() - 1][v[0].size() - 1];
    }
public:
    int myAtoi(string s) {
        int i = 0;
        //丢弃无用空格
        while (s[i] == ' ')++i;
        //检查符号
        int fuhao = 1;
        if (s[i] == '-') {
            fuhao = -1;
            ++i;
        }
        else if (s[i] == '+') {
            ++i;
        }
        //读取数字
        long long res = 0;
        while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
            res *= 10;
            res += s[i] - '0';
            ++i;
            if (res != (int)res) {
                if (fuhao == 1) {
                    return 2147483647;
                }
                else {
                    return -2147483648;
                }
            }
        }
        return res * fuhao;
    }
};



int main(){
    Solution a;
//    a.longestValidParentheses("(())()(()((");
//    a.isMatch("a", "ab*");
    a.myAtoi("2147483648");
    return 0;  
}