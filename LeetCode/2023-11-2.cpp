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
        //�����˶���ÿ�ν��������Ч��̫���ˣ������Ҿ���ʹ����״��������ṹ��������
        vector<list<int>> tree(n);
        for (int i = 0; i < n; ++i) {
            if (favorite[favorite[i]] == i) {
                if (favorite[i] > i) {
                    cp.emplace_back(i, favorite[i]);
                }
            }
            else {
                //tree������������ϵ��popular�����ڻ�����ϵ������ǰ�޷����֣�����ͬʱ����
                tree[favorite[i]].push_back(i);
                ++popular[favorite[i]];
            }
        }
        //�����cp�ڣ�����ֱ��ֱ���ƽ�����������ɻ�
        int res = 0;
        for (auto& e : cp) {
            int res_i1 = 1;
            int res_i2 = 1;
            dfs(res_i1, e.first, 1, tree, popular);
            dfs(res_i2, e.second, 1, tree, popular);
            res += res_i1 + res_i2;
        }
        //ȥ������û��ϲ�����˵�ϲ�������ǵ�ϲ���Ѿ�û�м�ֵ�ˣ�����������ϵ����Ҳû��Ҫ�о���
        //�Ż�
        queue<int> loser;
        for (int i = 0; i < n; ++i) {
            if (popular[i] == 0) {
                loser.push(i);
            }
        }
        while (!loser.empty()) {
            int tmp = loser.front();
            loser.pop();
            if (--popular[favorite[tmp]] == 0) {
                //�����������ϵ�ģ���ô��ֱ����-1�ˣ����ᷴ����������
                loser.push(favorite[tmp]);
            }
        }
        vector<bool> used(n, false);
        for (int i = 0; i < n; ++i) {
            if (popular[i] <= 0) {
                used[i] = true;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (used[i]) {
                continue;
            }
            used[i] = true;
            //dfs(res, used, favorite, i, i, favorite[i], 2);
            int j = favorite[i];
            used[j] = true;
            int t_count = 1;
            while (j != i) {
                j = favorite[j];
                used[j] = true;
                ++t_count;
            }
            res = max(res, t_count);
        }
        return res;
    }
private:
    //ֱ�����ţ�ԭ�������������
    void dfs(int& res, int root, int deep, vector<list<int>>& tree, vector<int>&popular) {
        //������ϵ�޷����뻷����ϵ�����������������������ϵ����ȥ������Ȼ��ô����϶Ȼ���ߣ���Ϊ��Ч��
        popular[root] = 0;
        res = max(deep, res);
        for (auto& child : tree[root]) {
            dfs(res, child, deep + 1, tree, popular);
        }
    }
};

int main() {
    Solution test;
    vector<int> favorite{ 1,0,0,2,1,4,7,8,9,6,7,10,8};
    //wx::create("[3,4,7,4,6,2,4,3,2]", favorite);
    cout << test.maximumInvitations(favorite);
    return 0;
}



