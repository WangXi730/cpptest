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
        //����ս���ж�
        if (status[u] == status[v]) {
            //��ͬ��Ӫ������β�����ս��
            continue;
        }
        else {
            //��֪��ݲŷ���ս��
            if (c1 == 'Y') {
                //v��֪��u�����
                if (status[v] == 0) {
                    //ֱ�ӽ���ս��
                    duel(fire, u, v);
                }
                else if (fire[v] > fire[u]) {
                    //v������ȷ���Լ���Ӯ
                    duel(fire, u, v);
                }
            }
            if (c2 == 'Y') {
                //u��֪��v�����
                if (status[v] == 0) {
                    //ֱ�ӽ���ս��
                    duel(fire, u, v);
                }
                else if (fire[v] < fire[u]) {
                    //v������ȷ���Լ���Ӯ
                    duel(fire, u, v);
                }
            }
        }
    }
    //ս����Ϊ0����Ϊ����
    string result(n, 'Y');
    for (int i = 0; i < n; ++i) {
        if (fire[i] == 0) {
            result[i] = 'N';
        }
    }
    cout << result;
}
// 64 λ������� printf("%lld")