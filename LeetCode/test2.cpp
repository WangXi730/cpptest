#include <iostream>
#include <vector>
#include <string>
using namespace std;

void duel(vector<int>& fire, int u, int v) {
    if (fire[u] > fire[v]) {
        fire[v] = 0;
    }
    else if (fire[u] < fire[v]) {
        fire[u] = 0;
    }
    else {
        fire[u] = 0;
        fire[v] = 0;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> arr{ "monster","human" };
    vector<int> status(n);
    vector<int> fire(n);
    for (int i = 0; i < n; ++i) {
        string s_tmp;
        cin >> s_tmp >> fire[i];
        if (s_tmp == arr[0]) {
            status[i] = 0;
        }
        else {
            status[i] = 1;
        }
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        char c1, c2;
        cin >> c1 >> c2;
        //进行战斗判断
        if (status[u] == status[v]) {
            //相同阵营无论如何不进行战斗
            continue;
        }
        else {
            //得知身份才发生战斗
            if (c1 == 'Y') {
                //v得知了u的身份
                if (status[v] == 0) {
                    //直接进行战斗
                    duel(fire, u, v);
                }
                else if (fire[v] > fire[u]) {
                    //v是人且确定自己能赢
                    duel(fire, u, v);
                }
            }
            if (c2 == 'Y') {
                //u得知了v的身份
                if (status[v] == 0) {
                    //直接进行战斗
                    duel(fire, u, v);
                }
                else if (fire[v] < fire[u]) {
                    //v是人且确定自己能赢
                    duel(fire, u, v);
                }
            }
        }
    }
    //战斗力为0则认为死亡
    string result(n, 'Y');
    for (int i = 0; i < n; ++i) {
        if (fire[i] == 0) {
            result[i] = 'N';
        }
    }
    cout << result;
}
// 64 位输出请用 printf("%lld")