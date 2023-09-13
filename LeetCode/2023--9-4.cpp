#include<iostream>
#include<vector>
#include<set>
#include<queue>

using namespace std;

class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        //���������ظ���·����Ϊ���ص�����
        set<int> from_left_forbidden_set;//���ܴ���ߵ�������
        set<int> from_right_forbidden_set;//���ܴ��ұߵ�������
        for (int i = 0; i < forbidden.size(); ++i) {
            from_left_forbidden_set.insert(forbidden[i]);
            from_right_forbidden_set.insert(forbidden[i]);
        }
        if ((from_left_forbidden_set.find(x) != from_left_forbidden_set.end() && from_right_forbidden_set.find(x) != from_right_forbidden_set.end())) {
            return -1;
        }
        queue<pair<int,int>> q;//idx : times
        q.push(make_pair(0,0));
        from_left_forbidden_set.insert(0);
        from_right_forbidden_set.insert(0);
        //��qΪ�գ���ô���е�·�����˾�ͷ������߲����ܵ���x��λ�ã���ôͬ����Ϊʧ��
        while (!q.empty()) {
            pair<int, int> node = q.front();
            q.pop();
            if (node.first == x) {
                return node.second;
            }
            if(from_left_forbidden_set.find(node.first + a) == from_left_forbidden_set.end() && !(node.first > x &&  a - b > 0)){
                from_left_forbidden_set.insert(node.first + a);
                from_right_forbidden_set.insert(node.first + a);
                q.push(make_pair(node.first + a, node.second + 1));
            }
            if (node.first - b > 0 && from_right_forbidden_set.find(node.first - b) == from_right_forbidden_set.end() && from_left_forbidden_set.find(node.first) != from_left_forbidden_set.end()) {
                from_right_forbidden_set.insert(node.first - b);
                q.push(make_pair(node.first - b, node.second + 1));
            }
        }
        return -1;
    }
};



int main() {
    vector<int>arr{ 1998 };
    Solution test;
    std::cout << test.minimumJumps(arr,1999,2000,2000) << std::endl;
    return 0;
}
