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
        //����ǻ���
        if (is_palindrome(s, i, j)) {
            tmp.push_back(s.substr(i, j - i));
        }
        else {
            //����ֱ���˳�
            return;
        }
        //�ݹ����������j == s.size
        if (j == s.size()) {
            res.push_back(tmp);
            return;
        }
        //����������Ѱ����һ������
        i = j;
        int n = tmp.size();
        for (j = i + 1; j <= s.size(); ++j) {
            dfs(res, tmp, i, j, s);
            while (n != tmp.size()) {
                //֮ǰ����ӳɹ������Ի���
                tmp.pop_back();
            }
        }
    }
    //�жϻ���
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
        //�򵥵ķ���һ���ֵ�
        vector<vector<string>> dict(26);
        for (auto& s : wordDict) {
            dict[s[0] - 'a'].push_back(s);
        }
        vector<bool> dp(s.size() + 1, false);
        dp[0] = true;
        for (int i = 0; i < s.size(); ++i) {
            //���ǰ�治��ƴ�ӣ����￪ʼ�Ͳ���
            if (!dp[i]) {
                continue;
            }
            //ȡ���������ĸ��ͷ�ĵ��ʵļ���
            vector<string>& v = dict[s[i] - 'a'];
            for (int j = 0; j < v.size(); ++j) {
                //����ж��Ƿ�ƥ��
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
        //�򵥵ķ���һ���ֵ�
        vector<vector<string>> dict(26);
        for (auto& s : wordDict) {
            dict[s[0] - 'a'].push_back(s);
        }
        vector<vector<int>> dp(s.size() + 1);
        //dp[1]�д���ŵ��±�����ţ������λ�ÿ�ͷ��ѡ�ĵ���
        //���dp[i].size()Ϊ0��1�������Ų���ѡ
        //����ѡ�����������
        //0��û�к��ʵ����ʹ������ַ������Դ�ͷ�и���λ��
        //1�����λ��û�к��ʵĿ���
        //��ͷ����һ�����ַ�����ʹ������������ɵ�ǰ���£���Ӱ����
        dp[0].push_back(-1);//��ͷ����Ҫע����ǣ��±�-1�����壬Ŀ���Ǹı��С
        //��ʼ�������dp����
        for (int i = 0; i < s.size(); ++i) {
            //���ǰ�治��ƴ�ӣ����￪ʼ�Ͳ���
            if (dp[i].size() == 0) {
                continue;
            }
            //ȡ���������ĸ��ͷ�ĵ��ʵļ���
            vector<string>& v = dict[s[i] - 'a'];
            for (int j = 0; j < v.size(); ++j) {
                //����ж��Ƿ�ƥ��
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
        //�ã�����ͨ��dp���ַ��Ѿ�������һ�������������Ч�ʵ����飬�������Ϳ�ʼ��ϵ���
        //ͨ����������㷨ʵ�֣�dp��ʵ����Ϊ�˷�ֹһ�δζ��ַ���ֱ�ӽ��бȽ�
        //�ü��ˣ����������������ߵ��յ��·����¼����
        vector<vector<int>> res;
        vector<int> tmp;
        dfs(res, tmp, dict, dp, s, 0);
        //���ڣ���������
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
        //�ݹ����������i==s.size()��i�ǵ�ǰ����
        if (i == s.size()) {
            res.push_back(tmp);
        }
        //��ʼȷ����һ������
        for (int j = 1; j < dp[i].size(); ++j) {
            tmp.push_back(dp[i][j]);
            //�ݹ�
            dfs(res, tmp, dict, dp, s, i + dict[s[i] - 'a'][dp[i][j]].size());
            //����
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