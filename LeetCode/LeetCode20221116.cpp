#include<iostream>
#include<vector>
#include<string>

using namespace std;
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> tmp;
        for (int j = 1; j <= s.size(); ++j) {
            dfs(res, tmp, 0, j, s);
            while(tmp.size()>=1)
                tmp.pop_back();
        }
        return res;
    }
private:
    void dfs(vector<vector<string>>& res, vector<string>& tmp, int i, int j, string& s) {
        //如果是回文
        if (is_palindrome(s, i, j)) {
            tmp.push_back(s.substr(i, j - i));
        }
        else {
            //否则直接退出
            return;
        }
        //递归结束条件，j == s.size
        if (j == s.size()) {
            res.push_back(tmp);
            return;
        }
        //接下来进行寻找下一个单词
        i = j;
        int n = tmp.size();
        for (j = i + 1; j <= s.size(); ++j) {
            dfs(res, tmp, i, j, s);
            while (n != tmp.size()) {
                //之前有添加成功，所以回溯
                tmp.pop_back();
            }
        }
    }
    //判断回文
    bool is_palindrome(string& s, int i, int j) {
        while (i < j) {
            if (s[i] != s[j - 1]) {
                return false;
            }
            ++i;
            --j;
        }
        return true;
    }
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        //简单的分类一下字典
        vector<vector<string>> dict(26);
        for (auto& s : wordDict) {
            dict[s[0] - 'a'].push_back(s);
        }
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        for (int i = 0; i < s.size(); ++i) {
            //如果前面不能拼接，这里开始就不能
            if (!dp[i]) {
                continue;
            }
            //取出以这个字母开头的单词的集合
            vector<string>& v = dict[s[i] - 'a'];
            for (int j = 0; j < v.size(); ++j) {
                //逐个判断是否匹配
                if (i + v[j].size() > s.size()) {
                    continue;
                }
                if (s.substr(i, v[j].size()) == v[j]) {
                    dp[i + v[j].size()] = true;
                }
            }
        }
        return dp[s.size()];
    }
public:
    vector<string> wordBreak2(string s, vector<string>& wordDict) {
        //简单的分类一下字典
        vector<vector<string>> dict(26);
        for (auto& s : wordDict) {
            dict[s[0] - 'a'].push_back(s);
        }
        vector<vector<int>> dp(s.size() + 1);
        //dp[1]中存放着的下标代表着：以这个位置开头可选的单词
        //如果dp[i].size()为0或1，代表着不可选
        //不可选有两种情况：
        //0、没有合适的组合使得这个字符串可以从头切割到这个位置
        //1、这个位置没有合适的开端
        //开头设置一个空字符串，使它拜托这个定律的前提下，不影响结果
        dp[0].push_back(-1);//开头，需要注意的是，下标-1无意义，目的是改变大小
        //开始创造这个dp数组
        for (int i = 0; i < s.size(); ++i) {
            //如果前面不能拼接，这里开始就不能
            if (dp[i].size() == 0) {
                continue;
            }
            //取出以这个字母开头的单词的集合
            vector<string>& v = dict[s[i] - 'a'];
            for (int j = 0; j < v.size(); ++j) {
                //逐个判断是否匹配
                if (i + v[j].size() > s.size()) {
                    continue;
                }
                if (s.substr(i, v[j].size()) == v[j]) {
                    if (dp[i + v[j].size()].empty())
                        dp[i + v[j].size()].push_back(-1);
                    dp[i].push_back(j);
                }
            }
        }
        //好，现在通过dp的手法已经创建了一个方便我们提高效率的数组，接下来就开始组合单词
        //通过深度优先算法实现，dp的实现是为了防止一次次对字符串直接进行比较
        //好极了，接下来把所有能走到终点的路径记录下来
        vector<vector<int>> res;
        vector<int> tmp;
        dfs(res, tmp, dict, dp, s, 0);
        //现在，穿插起来
        vector<string> result(res.size(), "");
        for (int i = 0; i < res.size(); ++i) {
            for (int j = 0; j < res[i].size(); ++j) {
                result[i] += dict[s[result[i].size() - j] - 'a'][res[i][j]] + " ";
            }
            result[i].pop_back();
        }
        return result;
    }
private:
    void dfs(vector<vector<int>>& res, vector<int>& tmp, vector<vector<string>>& dict, vector<vector<int>>& dp, string& s, int i) {
        //递归结束条件：i==s.size()，i是当前进度
        if (i == s.size()) {
            res.push_back(tmp);
        }
        //开始确定下一个进度
        for (int j = 1; j < dp[i].size(); ++j) {
            tmp.push_back(dp[i][j]);
            //递归
            dfs(res, tmp, dict, dp, s, i + dict[s[i] - 'a'][dp[i][j]].size());
            //回溯
            tmp.pop_back();
        }
    }
};


int main() {
    Solution test;
    //test.partition("aab");
    string s = "catsanddog";
    vector<string> v{ "cat","cats","and","sand","dog" };
    test.wordBreak2(s, v);
    return 0;
}