#include<iostream>
#include<vector>
#include<string>
#include<stack>
using namespace std;


class Solution {
//剑指 Offer 33. 二叉搜索树的后序遍历序列
public:
    bool verifyPostorder(vector<int>& postorder) {
        shared_ptr<int> root = nullptr;//当前结点是root左树，且在所有满足root条件的结点中，root的深度最大
        stack<int> st;//st记录 i 的父节点
        st.push(postorder[postorder.size() - 1]);
        for (int i = postorder.size() - 2; i >= 0;) {
            if (postorder[i] > st.top()) {
                //判断是否超过上界
                if (root != nullptr && *root < postorder[i]) {
                    return false;
                }
                //否则，视为正常,向右树探索
                st.push(postorder[i--]);
            }
            else {
                //如果不大于，说明进入左树了
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
                //继续探索右树
                st.push(postorder[i--]);
            }
        }
        //如果到最后都没找出来毛病，说明是二叉树的后续遍历
        return true;
    }
//剑指 Offer 19. 正则表达式匹配
public:
    bool isMatch(string s, string p) {
        vector<vector<bool>> dp(s.size() + 1, vector<bool>(p.size() + 1, false));
        //初始化第一行
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