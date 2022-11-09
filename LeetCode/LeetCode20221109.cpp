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
//��ʱ�ⷨ
//    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
//        //�������ô�죿ֱ�ӱ�����������
//        //��������н�
//        vector<vector<string>> res;
//        vector<string> tmp{ beginWord };
//        vector<bool> tmp_bool(wordList.size(), true);
//        _findLadders(res, tmp_bool, tmp, endWord, wordList);
//        if (res.empty()) {
//            return res;
//        }
//        //�ҳ�������С��
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
//    //res�����յķ���ֵ
//    //tmp_bool��������ǵ��ʵ�״̬���Ƿ��ʹ�ã�ÿһ������������һ�Σ���Ϊ����������μ����ϣ���ô�ͻᵼ���γɻ�����ԶҲ�߲���ȥ
//    //tmp�Ǳ����߹���·�ߣ�tmp�����һ��Ԫ���ǵ��µ�״̬��this_condition
//    //dest��destination�����յ���̬��Ҳ����endWord
//    void _findLadders(vector<vector<string>>& res, vector<bool>& tmp_bool, vector<string>& tmp, string& dest, vector<string>& wordList) {
//        //�ݹ����������this_condition == destination
//        string this_cond = tmp[tmp.size() - 1];
//        if (this_cond == dest) {
//            //tmp.push_back(dest);
//            res.push_back(tmp);
//            //tmp.pop_back();
//            return;
//        }
//        //����wordList
//        for (int i = 0; i < wordList.size(); ++i) {
//            //�����������ǿ�ʹ��״̬�����뵱ǰ���ʵ����Ϊ1���Ϳ��������������
//            if (tmp_bool[i] && only_dif(this_cond, wordList[i])) {
//                tmp.push_back(wordList[i]);
//                tmp_bool[i] = false;
//                _findLadders(res, tmp_bool, tmp, dest, wordList);
//                //����
//                tmp.pop_back();
//                tmp_bool[i] = true;
//            }
//        }
//    }
//    //�����������ʲ�ͬ����ĸ�ĸ����Ƿ���1
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
        //�ȱ���һ�Σ����wordList������endWord��ֱ�ӷ��ؼ���
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
        //���ÿһ�����ʱ�ʹ�õĽ׶�,-1��ʾû�б�ʹ��
        vector<int> road(wordList.size(), -1);
        //��־���
        bool finish = false;
        //�׶�
        //��������һ�׶ε�����
        for (int j = 0; j < road.size(); ++j) {
            if (only_dif(wordList[j], beginWord)) {
                road[j] = 0;//��0�׶ε�ֵ       
                if (endWord == wordList[j]) {
                    finish = true;
                }
            }
        }
        int i = 0;//iΪǰһ���׶�

        while (!finish) {
            for (int j = 0; j < road.size(); ++j) {
                if (road[j] == i) {
                    //��������û��ʹ�ù�������
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
        //���ڣ����е���̵Ŀ����Զ��Ѿ��õ��˱��棬�����еı仯���л�ԭ
        if (road[appear] == -1) {
            return {};
        }
        //��������һ��
        vector<vector<string>> res;
        vector<vector<string>> v(i+1);
        vector<bool> valuable(road.size(),false);//ѡ���м�ֵ�Ľ��
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
        //��ÿһ�����ܵĽ����¼
        for (int i = 0; i < road.size(); ++i) {
            if (road[i] != -1 && road[i] != -2) {
                v[road[i]].push_back(wordList[i]);
            }
        }
        vector<string> tmp(1, beginWord);
        //dfs��ѿ�����
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
                //����
                tmp.pop_back();
            }
        }
    }
    //�����������ʲ�ͬ����ĸ�ĸ����Ƿ���1
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