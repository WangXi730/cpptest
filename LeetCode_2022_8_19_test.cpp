#include<iostream>
#include<vector>
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
};

int main() {
	return 0;
}