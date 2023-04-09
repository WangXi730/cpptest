#include<iostream>
#include<vector>
#include<string>

using namespace std;


class Solution {
public:
    vector<string> addOperators(string num, int target) {
        string s;
        vector<string> res;
        int tmp = 0;
        for (int j = 0; j < num.size(); ++j) {
            tmp *= 10;
            tmp += num[j] - '0';
            s.push_back(num[j]);
            dfs(res, s, num, target, 1 + j, 0, tmp);
            if (tmp == 0) {
                break;
            }
        }
        return res;
    }
private:
    void dfs(vector<string>& res, string& s, string& num, int target, int i, int figure, int pre_figure) {
        if (i == num.size()) {
            if (figure + pre_figure == target) {
                res.emplace_back(s);
            }
            return;
        }
        int size = s.size();
        s.resize(size + 1);
        int tmp = 0;
        for (int j = 0; i + j < num.size(); ++j) {
            //step
            s.push_back(num[i + j]);
            s[s.size() - 2 - j] = '*';
            tmp *= 10;
            tmp += num[i + j] - '0';
            dfs(res, s, num, target, i + j + 1, figure, pre_figure * tmp);
            s[s.size() - 2 - j] = '+';
            dfs(res, s, num, target, i + j + 1, figure + pre_figure, tmp);
            s[s.size() - 2 - j] = '-';
            dfs(res, s, num, target, i + j + 1, figure + pre_figure, -tmp);
            if (tmp == 0) {
                break;
            }
        }
        //»ØËÝ
        s.resize(size);
    }
};

int main() {
    Solution test;
    test.addOperators("00",0);
	return 0;
}