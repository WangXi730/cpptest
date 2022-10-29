#include<iostream>
#include<vector>
#include<stack>
#include<map>

using namespace std;


// Definition for singly-linked list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        //���ͷ����Ƿ���Ҫ����
        while (head != nullptr && head->next != nullptr && head->val == head->next->val) {
            int t = head->val;
            while (head != nullptr && head->val == t) {
                ListNode* rm = head;
                head = head->next;
                free(rm);
            }
        }
        //�ߵ�����˵��ͷ�ڵ��Ѿ���ȷ��
        //ListNode* tmp = head->next;
        ListNode* pre = head;
        while (1) {
            if (pre->next != nullptr && pre->next->next != nullptr && pre->next->val == pre->next->next->val) {
                while (pre->next != nullptr && pre->next->next != nullptr && pre->next->val == pre->next->next->val) {
                    int t = pre->next->val;
                    while (pre->next != nullptr && pre->next->val == t) {
                        ListNode* rm = pre->next;
                        pre->next = pre->next->next;
                        free(rm);
                    }
                }
            }
            else {
                pre = pre->next;
            }
            if (pre == nullptr) {
                break;
            }
        }
        return head;
    }
public:
    int largestRectangleArea(vector<int>& heights) {
        int res = 0;
        heights.push_back(0);
        stack<pair<int, int>> st;
        st.push(make_pair(heights[0], 0));
        for (int i = 1; i < heights.size(); ++i) {
            if (heights[i] > st.top().first) {
                st.push(make_pair(heights[i], i));
            }
            else if(heights[i] == heights[i-1]){
                //ʲô������
            }
            else {
                int pre = 0;
                while (!st.empty() && st.top().first > heights[i]) {
                    pair<int, int> tmp = st.top();
                    st.pop();
                    pre = tmp.second;
                    res = max(res, tmp.first * (i - tmp.second));
                }
                st.push(make_pair(heights[i], pre));
            }
        }
        return res;
    }

};


int main() {
    Solution test;
    vector<int> v{ 4,2,0,3,2,5 };
    test.largestRectangleArea(v);
    return 0;
}