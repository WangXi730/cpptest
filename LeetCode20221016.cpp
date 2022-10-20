#include<iostream>
#include<vector>
#include<stack>
using namespace std;

  struct ListNode {
      int val;
      ListNode *next;
      ListNode(int x) : val(x), next(NULL) {}
  };
 
class Solution {
public:
    void deleteNode(ListNode* node) {
        ListNode*& tmp = node;
        while (tmp->next != nullptr) {
            tmp->val = tmp->next->val;
            tmp = tmp->next;
        }
        delete tmp;
        while (node->next != tmp) {
            node = node->next;
        }
        node->next = nullptr;
    }
    ListNode* partition(ListNode* head, int x) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* ptr = head;
        ListNode* last = head;
        ptr = ptr->next;
        last->next = nullptr;
        while (ptr != nullptr) {
            if (ptr->val < x) {
                ListNode* tmp = ptr;
                ptr = ptr->next;
                tmp->next = nullptr;
                push_front(head, tmp);
            }
            else {
                ListNode* tmp = ptr;
                ptr = ptr->next;
                tmp->next = nullptr;
                push_back(last, tmp);
            }
        }
        return head;
    }
    //Í·²å
    void push_front(ListNode*& dest, ListNode* node) {
        node->next = dest;
        dest = node;
    }
    //Î²²å
    void push_back(ListNode*& dest, ListNode* node) {
        while (dest->next != nullptr) {
            dest = dest->next;
        }
        dest->next = node;
        dest = node;
    }
};
class StackOfPlates {
public:
    StackOfPlates(int cap) :_cap(cap), v() {

    }

    void push(int val) {
        if (v.empty() || v[v.size() - 1].size() == _cap) {
            v.push_back(stack<int>());
        }
        v[v.size() - 1].push(val);
    }

    int pop() {
        while (v[v.size() - 1].size() == 0) {
            if (v.size() == 0) {
                return -1;
            }
            v.pop_back();
            if (v.size() == 0) {
                return -1;
            }
        }
        int res = v[v.size() - 1].top();
        v[v.size() - 1].pop();
        return res;
    }

    int popAt(int index) {
        int res = v[index].top();
        v[index].pop(); 
        if (v[index].size() == 0) {
            v.erase(v.begin() + index);
        }
        return res;
    }
private:
    int _cap;
    vector<stack<int>> v;
};


int main() {
    StackOfPlates st(1);
    st.push(1);
    st.push(2);
    cout<<st.popAt(1);
    st.pop();
    st.pop();
    return 0;
}