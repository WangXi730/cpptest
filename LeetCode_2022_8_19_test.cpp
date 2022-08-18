#include<iostream>
#include<vector>
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
};

int main() {
	return 0;
}