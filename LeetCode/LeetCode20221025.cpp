#include<iostream>
#include<string>
#include<algorithm>
#include<vector>
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
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<vector<string>> rows;
        int char_size = 0;
        vector<string> row;
        for (int i = 0; i < words.size(); ++i) {
            if (char_size + words[i].size() > maxWidth) {
                rows.push_back(row);
                vector<string> tmp;
                row.swap(tmp);
                char_size = 0;
            }
            row.push_back(words[i]);
            char_size += words[i].size()+1;
        }
        rows.push_back(row);
        vector<string> res;
        for (int i = 0; i < rows.size()-1; ++i) {
            string tmp(maxWidth, ' ');
            int tmp_sz = 0;
            for (int j = 0; j < rows[i].size(); ++j) {
                tmp_sz += rows[i][j].size();
            }
            if (rows[i].size() == 1) {
                memcpy(&tmp[0], &rows[i][0][0], rows[i][0].size());
                res.push_back(tmp);
                continue;
            }
            int block_sz = (maxWidth - tmp_sz) / (rows[i].size() - 1);
            int mod = (maxWidth - tmp_sz) % (rows[i].size() - 1);
            int k = 0;
            int ki = 0;
            for (int j = 0; j < maxWidth; ++j) {
                tmp[j] = rows[i][k][ki++];
                if (ki == rows[i][k].size()) {
                    ki = 0;
                    ++k;
                    j += block_sz;
                    if (--mod >= 0) {
                        ++j;
                    }
                }
            }
            res.push_back(tmp);
        }
        string tmp(maxWidth, ' ');
        int idx = 0;
        for (int i = 0; i < rows[rows.size()-1].size(); ++i) {
            memcpy(&tmp[idx], &rows[rows.size() - 1][i][0], rows[rows.size() - 1][i].size());
            idx += rows[rows.size() - 1][i].size() + 1;
        }
        res.push_back(tmp);
        return res;
    }
};


int main() {
    Solution test;
    //test.isNumber("+.1");
    //test.addBinary("1010", "1011");
    vector<string> v{ "This", "is", "an", "example", "of", "text", "justification." };
    test.fullJustify(v, 16);
    return 0;
}