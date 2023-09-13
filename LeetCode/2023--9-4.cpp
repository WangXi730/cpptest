#include<iostream>
#include<vector>
#include<set>
#include<queue>

using namespace std;

class Solution {
public:
    int minimumJumps(vector<int>& forbidden, int a, int b, int x) {
        //不允许走重复的路，因为会重蹈覆辙
        set<int> from_left_forbidden_set;//不能从左边到达这里
        set<int> from_right_forbidden_set;//不能从右边到达这里
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
        //当q为空，那么所有的路都到了尽头，如果走不到能到达x的位置，那么同样视为失败
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
