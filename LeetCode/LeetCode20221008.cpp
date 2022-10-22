#include<iostream>
#include<stack>
#include<vector>
#include<map>

using namespace std;
  struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
  };
 
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) {
            return nullptr;
        }
        else if (lists[0] == nullptr) {
            return nullptr;
        }
        multimap<int, ListNode*> mp;
        for (ListNode*& l : lists) {
            ListNode* node = l;
            while (node != nullptr) {
                mp.insert({ node->val,node });
                node = node->next;
            }
        }
        ListNode* res = mp.begin()->second;
        ListNode* node = res;
        auto it = mp.begin();
        for (++it; it != mp.end(); ++it) {
            node->next = it->second;
            node = node->next;
        }
        return res;
    }
};

int main() {
//    Solution a;
//    ListNode node1(1); //[[1, 4, 5], [1, 3, 4], [2, 6]]
//    node1.next = new ListNode(4);
//    node1.next->next = new ListNode(5);
//    ListNode node2(1);
//    node2.next = new ListNode(3);
//    node2.next->next = new ListNode(4);
//    ListNode node3(2);
//    node3.next = new ListNode(6);
//    std::vector<ListNode*> l = { &node1, &node2, &node3 };
//    a.mergeKLists(l);
    int a = -2147483648;
    int b = abs(a);
    std::cout << b << std::endl;
    return 0;
}