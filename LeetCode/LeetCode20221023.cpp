#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<set>
#include<assert.h>
#include"LeetCode_array.hpp"

using namespace std;

struct func1;


class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> res;//����ֵ
        vector<string> tmp(n, string(n, '.'));//��������
        vector<bool> col(n, false);//false��ʾ��j��û�лʺ�ռ��
        vector<bool> up(n * 2 - 1, false);//false��ʾ��ؾ�Ϊ n-j-1 ��������������û�лʺ�
        vector<bool> down(n * 2 - 1, false);//false��ʾ��ؾ� j �ķ�����������û�лʺ�
        func(res, tmp, col, up, down, 0, n);
        return res;
    }
private:
    void func(vector<vector<string>>& res, vector<string>& tmp, vector<bool> col, vector<bool>& up, vector<bool>& down, int i, int n) {//i��������
        //�ݹ��������
        if (i == n) {
            res.push_back(tmp);
        }
        //����һ�е�j�зֱ�д��
        for (int j = 0; j < n; ++j) {
            if (col[j] || up[n - j - 1 + i] || down[i + j]) {
                continue;
            }
            //���������û�У���ô�����λ�÷��»ʺ󣬲��޸ı��
            tmp[i][j] = 'Q';
            col[j] = true;
            up[n - j - 1 + i] = true;
            down[i + j] = true;
            //ִ����һ��
            func(res, tmp, col, up, down, i, n);
            //���ݣ��ý�����һ���Դ�
            tmp[i][j] = '.';
            col[j] = false;
            up[n - j - 1 + i] = false;
            down[i + j] = false;
        }
    }
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        int i = 0;
        int idx = 0;
        int up = 0;
        int down = 0;
        int left = 0;
        int right = 0;
        vector<int> res(matrix.size() * matrix[0].size());

        while (1) {
            if (idx >= res.size()) {
                return res;
            }
            switch (i++ % 4) {
            case 0:
                for (int j = left; j < matrix[0].size() - right; ++j) {
                    res[idx++] = matrix[up][j];
                }
                ++up;
                break;
            case 1:
                for (int j = up; j < matrix.size() - down; ++j) {
                    res[idx++] = matrix[j][matrix[0].size() - 1 - right];
                }
                ++right;
                break;
            case 2:
                for (int j = matrix[0].size() - 1 - right; j >= left; --j) {
                    res[idx++] = matrix[matrix.size() - 1 - down][j];
                }
                ++down;
                break;
            case 3:
                for (int j = matrix.size() - 1 - down; j >= up; --j) {
                    res[idx++] = matrix[j][left];
                }
                ++left;
                break;
            }
        }
        return res;
    }
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = 0;
        for (int i = 0; i < intervals.size(); ++i) {
            if (intervals[i][1] > n) {
                n = intervals[i][1];
            }
        }
        ++n;
        bool* mp = (bool*)malloc(sizeof(bool) * n);
        vector<vector<int>> res;
        set<int> null_size;
        memset(mp, false, n * sizeof(bool));
        for (int i = 0; i < intervals.size(); ++i) {
            if (intervals[i][0] == intervals[i][1]) {
                null_size.insert(intervals[i][0]);
            }
            else {
                memset(mp + intervals[i][0], true, intervals[i][1] - intervals[i][0]);
            }
        }
        int first = -1;
        for (int i = 0; i < n; ++i) {
            if (mp[i]) {
                if (first == -1) {
                    first = i;
                }
            }
            else {
                if (first != -1) {
                    res.push_back({ first,i });
                    first = -1;
                }
            }
        }
        if (first != -1) {
            res.push_back({ first,n - 1 });
        }
        for (const int& i : null_size) {
            if (!mp[i] && (i == 0 || !mp[i - 1])) {
                res.push_back({ i,i });
            }
        }
        free(mp);
        return res;
    }
    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        if (intervals.empty()) {
            return { newInterval };
        }
        vector<vector<int>> res;
        int uninserted = true;
        for (int i = 0; i < intervals.size(); ++i) {
            if (newInterval[0] < intervals[i][0] && uninserted) {
                uninserted = false;
                if (res.empty()) {
                    res.push_back(newInterval);
                }
                else if (newInterval[0] <= res[res.size() - 1][1]) {
                    if (newInterval[1] > res[res.size() - 1][1]) {
                        res[res.size() - 1][1] = newInterval[1];
                    }
                }
                else {
                    while (i < intervals.size() && newInterval[1] >= intervals[i][0]) {
                        if (newInterval[1] < intervals[i][1]) {
                            newInterval[1] = intervals[i][1];
                        }
                        ++i;
                    }
                    res.push_back(newInterval);
                    if (i >= intervals.size()) {
                        break;
                    }
                }
            }
            if (res.empty() || res[res.size() - 1][1] < intervals[i][1]) {
                if (!res.empty() && res[res.size() - 1][1] >= intervals[i][0]) {
                    res[res.size() - 1][1] = intervals[i][1];
                }
                else {
                    res.push_back(intervals[i]);
                }
            }
        }
        if (uninserted) {
            if (res[res.size() - 1][1] >= newInterval[0]) {
                if (newInterval[1] > res[res.size() - 1][1]) {
                    res[res.size() - 1][1] = newInterval[1];
                }
            }
            else {
                res.push_back(newInterval);
            }
        }
        return res;
    }
};



struct func1 {
    bool operator()(const vector<int>& a,const vector<int>& b) {
        return a[0] <= b[0];
    }
};

int main() {
    Solution test;
    vector<vector<int>> intervals{ {1,2},{1,5} };
    func1 f;
    sort(intervals.begin(), intervals.end());
    return 0;
}