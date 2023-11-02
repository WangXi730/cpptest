#include"LeetCodeTools.hpp"

leetcode

class Solution {
public:
    int maximumInvitations(vector<int>& favorite) {
        //��ÿһ��Ԫ��Ϊ��һ��������ˣ�����һ��
        //���м�֦���ռ������˱�������ϲ��
        int n = favorite.size();
        vector<int> popular(n, 0);
        vector<pair<int, int>> cp;//����ϲ���Ŀ������cp
        vector<bool> is_cp(n, false);
        for (int i = 0; i < n; ++i) {
            if (favorite[favorite[i]] == i && favorite[i] > i) {
                cp.emplace_back(i, favorite[i]);
                is_cp[i] = true;
                is_cp[favorite[i]] = true;
            }
            ++popular[favorite[i]];
        }
        //�����cp�ڣ�����ֱ��ֱ���ƽ�����������ɻ�
        int res = 0;
        vector<bool> used(n, false);
        for (auto& e : cp) {
            int res_i1 = 1;
            int res_i2 = 1;
            for (int i = 0; i < n; ++i) {
                if (favorite[i] == e.first && i != e.second) {
                    dfs(res_i1, i, 2, favorite);
                }
                if (favorite[i] == e.second && i != e.first) {
                    dfs(res_i2, i, 2, favorite);
                }
            }
            res += res_i1 + res_i2;
        }
        //ȥ������û��ϲ�����˵�ϲ�������ǵ�ϲ���Ѿ�û�м�ֵ��
        while (1) {
            bool end = true;
            for (int i = 0; i < n; ++i) {
                if (popular[i] == 0) {
                    popular[i] = -1;
                    --popular[favorite[i]];
                    end = false;
                }
            }
            if (end) {
                break;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (popular[i] <= 0) {
                used[i] = true;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (popular[i] <= 0) {
                continue;
            }
            used[i] = true;
            used[favorite[i]] = true;
            dfs(res, used, favorite, i, i, favorite[i], 2);
            used[i] = false;
            used[i] = false;
        }
        return res;
    }
private:
    //ֱ�����ţ�ԭ�������������
    void dfs(int& res, int root, int deep, vector<int>& favorite) {
        res = max(deep, res);
        for (int child = 0; child < favorite.size(); ++child) {
            if (favorite[child] = root) {
                dfs(res, child, deep + 1, favorite);
            }
        }
    }
    //��״����
    void dfs(int& res, vector<bool>& used, vector<int>& favorite, int left, int right, int i, int tmp_res) {
        //�����ߵ��˾���iϲ���ģ���ô���������Գ�����������Ϊ����������ѡ��ͬʱ����һ�μ�¼
        if (left == favorite[i]) {
            //��¼
            res = max(res, tmp_res);
            //����
            for (int j = 0; j < used.size(); ++j) {
                //��������û���������Ϳ���������
                if (!used[j]) {
                    used[j] = true;
                    dfs(res, used, favorite, i, right, j, tmp_res + 1);
                    used[j] = false;
                }
            }
        }
        else if (right == favorite[i]) {
            //��������¼������
            res = max(res, tmp_res);
            return;
        }
        else {
            //���ܼ������ˣ���������i
            if (!used[favorite[i]]) {
                used[favorite[i]] = true;
                dfs(res, used, favorite, i, right, favorite[i], tmp_res + 1);
                used[favorite[i]] = false;
            }
        }
    }
};


int main() {
    Solution test;
    vector<int> favorite{ 2,2,1,2 };
    //wx::create("[3,4,7,4,6,2,4,3,2]", favorite);
    cout << test.maximumInvitations(favorite);
    return 0;
}



