#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include"LeetCode_array.hpp"
using namespace std;

class Solution {
public:
    string simplifyPath(string path) {
        //��Ҫβ�塢βɾ����ͷ��ʼ˳�����������ʹ��vector
        vector<string> path_v;
        int begin = 0;
        for (int i = 1; i < path.size(); ++i) {
            if (path[i] == '/') {
                if (i == begin + 1) {
                    begin = i;
                    continue;
                }
                string pwd(path.begin() + begin, path.begin() + i);
                begin = i;
                if (pwd == "/.") {
                    continue;
                }
                else if (pwd == "/..") {
                    if(!path_v.empty())
                        path_v.pop_back();
                    continue;
                }
                path_v.push_back(pwd);
            }
        }
        if (path[path.size() - 1] != '/') {
            string s(path.begin() + begin, path.end());
            if (s == "/.") {
                
            }
            else if (s == "/..") {
                if (!path_v.empty())
                    path_v.pop_back();
            }
            else {
                path_v.push_back(s);
            }
        }
        stringstream res;
        for (int i = 0; i < path_v.size(); ++i) {
            res << path_v[i];
        }
        if (res.str() == "") {
            res << "/";
        }
        return res.str();
    }
public:
//    //��ʱʧ�ܵı����ⷨ
//    int minDistance(string word1, string word2) {
//        if (word1.size() == 0) {
//            return word2.size();
//        }
//        else if (word2.size() == 0) {
//            return word1.size();
//        }
//        //res��¼���п��ܵı任
//        vector<vector<int>> res;
//        //tmp�Ǿ����ʵ��
//        vector<int> tmp(word1.size(), -1);
//        //Ѱ�ҵ�λ�ã�����word2���±�
//        int i = 0;
//        //�Ѿ�Ѱ�ҵ���λ�ã���word1������ҪѰ�ҵ���С�±�
//        int j = 0;
//        func(res, tmp, i, j, word1, word2);
//        //Ѱ��res�У������������ٵ�
//        int result = -1;
//        for (i = 0; i < res.size(); ++i) {
//            int t = 0;
//            int pre = -1;
//            int sol = 0;
//            for (j = 0; j < res[i].size(); ++j) {
//                if (res[i][j] == -1) {
//                    t += 1;
//                    sol += 1;
//                }
//                else {
//                    //������Ҫɾ���Ŀ飬���ǳ�֮Ϊ���鷳��
//                    int problem = res[i][j] - pre - 1;
//                    pre = res[i][j];
//                    problem -= sol;
//                    if (problem > 0) {
//                        t += problem;
//                    }
//                    sol = 0;
//                }
//            }
//            if (pre!=-1 && word2.size() - 1 != pre) {
//                int problem = word2.size() - 1 - pre;
//                problem -= sol;
//                if (problem > 0) {
//                    t += problem;
//                }
//            }
//            if (result == -1 || t < result) {
//                result = t;
//            }
//        }
//        return result;
//    }
//private:
//    void func(vector<vector<int>>& res, vector<int>& tmp, int i, int j, string& word1, string& word2) {
//        if (j > tmp.size()) {
//            res.push_back(tmp);
//        }
//        bool no_find = true;
//        for (int ki = i; ki < word2.size(); ++ki) {
//            for (int kj = j; kj < word1.size(); ++kj) {
//                if (word1[kj] == word2[ki]) {
//                    //�ݹ�
//                    tmp[kj] = ki;
//                    func(res, tmp, ki+1, kj+1, word1, word2);
//                    //����
//                    tmp[kj] = -1;
//                    no_find = false;
//                }
//            }
//        }
//        if (no_find) {
//            res.push_back(tmp);
//        }
//    }
    public:
        int minDistance(string word1, string word2) {
            vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
            for (int i = 0; i < word1.size()+1; ++i) {
                dp[i][0] = i;
            }
            for (int i = 0; i < word2.size()+1; ++i) {
                dp[0][i] = i;
            }
            for (int i = 1; i < word1.size()+1; ++i) {
                for (int j = 1; j < word2.size()+1; ++j) {
                    int a;
                    int b = dp[i - 1][j] + 1;
                    int c = dp[i][j - 1] + 1;
                    if (word1[i - 1] == word2[j - 1]) {
                        a = dp[i - 1][j - 1];
                    }
                    else {
                        a = dp[i - 1][j - 1] + 1;
                    }
                    dp[i][j] = min(min(a, b), c);
                }
            }
            return dp[word1.size()][word2.size()];
        }
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        //������
        int def = 0;
        int sup = matrix.size() - 1;
        int left = 0;
        int right = matrix[0].size() - 1;
        if (matrix[sup][right]<target || matrix[def][left]>target) {
            return false;
        }
        else if (matrix[sup][right] == target || matrix[def][left] == target) {
            return true;
        }
        //���ֲ���
        while (sup > def) {
            int mid = (sup + def) / 2;
            if (matrix[mid][left] > target) {
                sup = mid - 1;
            }
            else if (matrix[mid][right] < target) {
                def = mid + 1;
            }
            else {
                sup = mid;
                def = mid;
            }
        }
        if (sup < def) {
            return false;
        }
        //��һ�н��ж��ֲ���
        int i = sup;
        while (right > left) {
            int mid = (left + right) / 2;
            if (matrix[i][mid] > target) {
                right = mid - 1;
            }
            else if (matrix[i][mid] < target) {
                left = mid + 1;
            }
            else {
                return true;
            }
        }
        if (left > right) {
            return false;
        }
        return matrix[i][left] == target;
    }
};



int main() {
    Solution test;
    //test.simplifyPath("/a//b////c/d//././/..");
    //std::cout << test.minDistance("horse","ros")
    vector<vector<int>> matrix{ {1,3,5,7},{10,11,16,20},{23,30,34,60} };
    test.searchMatrix(matrix,3);
    return 0;
}