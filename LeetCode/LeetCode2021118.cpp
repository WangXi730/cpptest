#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

 //Definition for singly-linked list.
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
  class List {
  public:
      ListNode* head = nullptr;
      List(initializer_list<int> l) {
          ListNode* ptr = new ListNode(*l.begin());
          head = ptr;
          for (int i = 1; i < l.size(); ++i) {
              ptr->next = new ListNode(*(l.begin() + i));
              ptr = ptr->next;
          }
      }
      ~List() {
          while (head) {
              ListNode* ptr = head;
              head = head->next;
              delete ptr;
          }
      }
  };

class Solution {
public:
    void reorderList(ListNode* head) {
        ListNode* left = head;
        stack<ListNode*> right;
        while (head != nullptr) {
            right.push(head);
            head = head->next;
        }
        int i = 0;
        int n = right.size();
        head = left;
        while (i++ < n / 2) {
            ListNode* ptr = left->next;
            left->next = right.top();
            right.top()->next = ptr;
            left = ptr;
            right.pop();
        }
    }
};


int main() {
    List l = { 1,2,3,4 };
    Solution test;
    test.reorderList(l.head);
    return 0;
}