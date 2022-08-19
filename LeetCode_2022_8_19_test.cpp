#include<iostream>
#include<vector>
#include<string>
#include<stack>
using namespace std;


class Solution {
//��ָ Offer 33. �����������ĺ����������
public:
    bool verifyPostorder(vector<int>& postorder) {
        shared_ptr<int> root = nullptr;//��ǰ�����root������������������root�����Ľ���У�root��������
        stack<int> st;//st��¼ i �ĸ��ڵ�
        st.push(postorder[postorder.size() - 1]);
        for (int i = postorder.size() - 2; i >= 0;) {
            if (postorder[i] > st.top()) {
                //�ж��Ƿ񳬹��Ͻ�
                if (root != nullptr && *root < postorder[i]) {
                    return false;
                }
                //������Ϊ����,������̽��
                st.push(postorder[i--]);
            }
            else {
                //��������ڣ�˵������������
                int tmp = st.top();
                while (!st.empty() && st.top() > postorder[i]) {
                    tmp = st.top();
                    st.pop();
                }
                if (root.get() == nullptr) {
                    root.reset(new int(tmp));
                }
                else {
                    *root = tmp;
                }
                //����̽������
                st.push(postorder[i--]);
            }
        }
        //��������û�ҳ���ë����˵���Ƕ������ĺ�������
        return true;
    }
//��ָ Offer 19. ������ʽƥ��
public:
    bool isMatch(string s, string p) {
        vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, false));
        //��ʼ����һ��
        dp[0][0] = true;
        for (int i = 1; i <= p.size(); ++i) {
            if (p[i - 1] == '*') {
                dp[0][i] = dp[0][i - 2];
            }
        }
        for (int i = 1; i < dp.size(); ++i) {
            for (int j = 1; j < dp[0].size(); ++j) {
                if (s[i - 1] == p[j - 1] || p[j - 1] == '.') {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else if (p[j - 1] != '.' && p[j - 1] != '*' && p[j - 1] != s[i - 1]) {
                }
                else if (p[j - 1] == '*') {
                    if (s[i - 1] == p[j - 2] || p[j - 2] == '.') {
                        dp[i][j] = dp[i][j - 2] || dp[i - 1][j];
                    }
                    else {
                        dp[i][j] = dp[i][j - 2];
                    }
                }
            }
        }
        return dp[s.size()][p.size()];
    }
};

int main() {
    Solution a;
    a.isMatch("aa", "a*");
	return 0;
}