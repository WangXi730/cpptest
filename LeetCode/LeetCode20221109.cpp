#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0;
        int right = s.size() - 1;
        while (left < right) {
            while (left < right && (s[left] > '9' || s[left] < '0') && (s[left] < 'a' || s[left]>'z') && (s[left] < 'A' || s[left]>'Z')) {
                ++left;
            }
            while (left < right && (s[right] > '9' || s[right] < '0') && (s[right] < 'a' || s[right]>'z') && (s[right] < 'A' || s[right]>'Z')) {
                --right;
            }
            if (left < right) {
                if (s[left] == s[right]) {
                    ++left;
                    --right;
                    continue;
                }
                if (s[left] >= 'a' && s[left] <= 'z') {
                    s[left] = s[left] - 'a' + 'A';
                }
                else if(s[left] >= 'A' && s[left] <= 'Z') {
                    s[left] = s[left] - 'A' + 'a';
                }
                if (s[left] == s[right]) {
                    ++left;
                    --right;
                    continue;
                }
                return false;
            }
        }
        return true;
    }
public:
//超时解法
//    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
//        //不会解怎么办？直接暴力淦起来！
//        //先求出所有解
//        vector<vector<string>> res;
//        vector<string> tmp{ beginWord };
//        vector<bool> tmp_bool(wordList.size(), true);
//        _findLadders(res, tmp_bool, tmp, endWord, wordList);
//        if (res.empty()) {
//            return res;
//        }
//        //找出长度最小的
//        int m = res[0].size();
//        for (int i = 0; i < res.size(); ++i) {
//            if (res[i].size() < m) {
//                m = res[i].size();
//            }
//        }
//        vector<vector<string>> result;
//        for (int i = 0; i < res.size(); ++i) {
//            if (res[i].size() == m) {
//                result.push_back(res[i]);
//            }
//        }
//        return result;
//    }
//private:
//    //res是最终的返回值
//    //tmp_bool是用来标记单词的状态，是否可使用，每一个单词最多出现一次，因为如果出现两次及以上，那么就会导致形成环，永远也走不出去
//    //tmp是本次走过的路线，tmp的最后一个元素是当下的状态：this_condition
//    //dest是destination，最终的形态，也就是endWord
//    void _findLadders(vector<vector<string>>& res, vector<bool>& tmp_bool, vector<string>& tmp, string& dest, vector<string>& wordList) {
//        //递归结束条件：this_condition == destination
//        string this_cond = tmp[tmp.size() - 1];
//        if (this_cond == dest) {
//            //tmp.push_back(dest);
//            res.push_back(tmp);
//            //tmp.pop_back();
//            return;
//        }
//        //遍历wordList
//        for (int i = 0; i < wordList.size(); ++i) {
//            //如果这个单词是可使用状态，且与当前单词的相差为1，就可以试试这个单词
//            if (tmp_bool[i] && only_dif(this_cond, wordList[i])) {
//                tmp.push_back(wordList[i]);
//                tmp_bool[i] = false;
//                _findLadders(res, tmp_bool, tmp, dest, wordList);
//                //回溯
//                tmp.pop_back();
//                tmp_bool[i] = true;
//            }
//        }
//    }
//    //计算两个单词不同的字母的个数是否是1
//    bool only_dif(string& s1, string& s2) {
//        bool count = true;
//        for (int i = 0; i < s1.size(); ++i) {
//            if (s1[i] != s2[i]) {
//                if (count) {
//                    count = false;
//                }
//                else {
//                    return count;
//                }
//            }
//        }
//        return !count;
//    }
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        //先遍历一次，如果wordList不存在endWord，直接返回即可
        int appear = -1;
        for (int i = 0; i < wordList.size(); ++i) {
            if (wordList[i] == endWord) {
                appear = i;
                break;
            }
        }
        if (appear == -1) {
            return {};
        }
        //标记每一个单词被使用的阶段,-1表示没有被使用
        vector<int> road(wordList.size(), -1);
        //标志完成
        bool finish = false;
        //阶段
        //单独进行一阶段的搜索
        for (int j = 0; j < road.size(); ++j) {
            if (only_dif(wordList[j], beginWord)) {
                road[j] = 0;//第0阶段的值       
                if (endWord == wordList[j]) {
                    finish = true;
                }
            }
        }
        int i = 0;//i为前一个阶段

        while (!finish) {
            for (int j = 0; j < road.size(); ++j) {
                if (road[j] == i) {
                    //遍历其他没有使用过的数字
                    string this_word = wordList[j];
                    for (int k = 0; k < road.size(); ++k) {
                        if (road[k] == -1 && only_dif(this_word, wordList[k])) {
                            road[k] = i + 1;
                            if (endWord == wordList[k]) {
                                finish = true;
                            }
                        }
                    }
                }
            }
            ++i;
            if (i > road.size()) {
                return {};
            }
        }
        //现在，所有的最短的可能性都已经得到了保存，对所有的变化进行还原
        if (road[appear] == -1) {
            return {};
        }
        //反方向走一遍
        vector<vector<string>> res;
        vector<vector<string>> v(i+1);
        vector<bool> valuable(road.size(),false);//选出有价值的结点
        valuable[appear] = true;
        while (i > 0) {
            for (int j = 0; j < wordList.size(); ++j) {
                if (road[j] == i) {
                    string s = wordList[j];
                    for (int k = 0; k < wordList.size(); ++k) {
                        if (road[k] == i - 1 && only_dif(wordList[k], s)) {
                            valuable[k] = true;
                        }
                        
                    }
                }
            }
            --i;
        }
        for (int j = 0; j < valuable.size(); ++j) {
            if (!valuable[j]) {
                road[j] = -2;
            }
        }
        //将每一步可能的结果收录
        for (int i = 0; i < road.size(); ++i) {
            if (road[i] != -1 && road[i] != -2) {
                v[road[i]].push_back(wordList[i]);
            }
        }
        vector<string> tmp(1, beginWord);
        //dfs求笛卡尔积
        dfs(res, tmp, v);
        return res;
    }
private:
    void dfs(vector<vector<string>>& res, vector<string>& tmp, vector<vector<string>>& v) {
        if (tmp.size() > v.size()) {
            res.push_back(tmp);
            return;
        }
        int n = tmp.size() - 1;
        for (int i = 0; i < v[n].size(); ++i) {
            if (only_dif(tmp[n], v[n][i])) {
                tmp.push_back(v[n][i]);
                dfs(res, tmp, v);
                //回溯
                tmp.pop_back();
            }
        }
    }
    //计算两个单词不同的字母的个数是否是1
    bool only_dif(string& s1, string& s2) {
        bool count = true;
        for (int i = 0; i < s1.size(); ++i) {
            if (s1[i] != s2[i]) {
                if (count) {
                    count = false;
                }
                else {
                    return count;
                }
            }
        }
        return !count;
    }
};

int main() {
    //string s = "A man, a plan, a canal: Panama";
    Solution test;
    //test.isPalindrome("0P");
    vector<string> v{ "hot", "dog" };
    test.findLadders("hot"
        ,"dog",
        v);
    return 0;
}