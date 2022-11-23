#include<iostream>
#include<unordered_map>
#include<list>
#include<algorithm>
#include"LeetCode_array.hpp"

using namespace std;
class LRUCache {
public:
    LRUCache(int capacity) : _capacity(capacity) {

    }

    int get(int key) {
        if (hash.find(key) == hash.end()) {
            return -1;
        }
        int res = hash[key]->second;
        l.erase(hash[key]);
        l.push_front(make_pair(key,res));
        hash[key] = l.begin();
        return res;
    }

    void put(int key, int value) {
        if (hash.find(key) != hash.end()) {
            *hash[key] = make_pair(key,value);
            get(key);
            return;
        }
        else if (_capacity == l.size()) {
            hash.erase(l.rbegin()->first);
            l.pop_back();
        }
        l.push_front(make_pair(key,value));
        hash[key] = l.begin();
    }
//private:
    int _capacity;
    unordered_map<int, list<pair<int,int>>::iterator> hash;
    list<pair<int,int>> l;
};

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
    ListNode* insertionSortList(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* res = head;
        ListNode* ptr = head->next;
        if (ptr->val < res->val) {
            ListNode* tmp = ptr->next;
            ptr->next = res;
            res->next = tmp;
            res = ptr;
        }
        ptr = res->next;
        while (ptr->next != nullptr) {
            ListNode* tmp = ptr->next;
            if (tmp->val < res->val) {
                ListNode* ttmp = tmp->next;
                tmp->next = res;
                res = tmp;
                ptr->next = ttmp;
                continue;
            }
            else if (ptr->val < tmp->val) {
                ptr = tmp;
                continue;
            }
            ptr->next = ptr->next->next;
            ListNode* move_ptr = res;
            while (move_ptr->next->val < tmp->val) {
                move_ptr = move_ptr->next;
            }
            tmp->next = move_ptr->next;
            move_ptr->next = tmp;
        }
        return res;
    }
public:
    ListNode* sortList(ListNode* head) {
        vector<int> v;
        ListNode* ptr = head;
        while (ptr != nullptr) {
            v.push_back(ptr->val);
            ptr = ptr->next;
        }
        sort(v.begin(), v.end());
        ptr = head;
        int i = 0;
        while (ptr != nullptr) {
            ptr->val = v[i++];
            ptr = ptr->next;
        }
        return head;
    }

};

class List {
public:
    ListNode* head;
    List(initializer_list<int> initial) {
        initializer_list<int>::iterator it = initial.begin();
        head = new ListNode(*it);
        ++it;
        ListNode* ptr = head;
        while (it != initial.end()) {
            ptr->next = new ListNode(*it);
            ptr = ptr->next;
            ++it;
        }
    }
};

int main() {
    //string s = "[[2],[1,0],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]";
    //string s2 = R"(["LRUCache","put","put","get","put","get","put","get","get","get"])";
    //array_to_c(s);
    //array_to_c(s2);
    //vector<vector<int>> val = { {2},{1,0},{2,2},{1},{3,3},{2},{4,4},{1},{3},{4} };
    //vector<string> how = { "LRUCache","put","put","get","put","get","put","get","get","get" };
    //LRUCache test(val[0][0]);
    //for (int i = 1; i < how.size(); ++i) {
    //    if (how[i] == "put") {
    //        test.put(val[i][0], val[i][1]);
    //        cout << "NULL" << "\t";
    //    }
    //    else {
    //        cout << test.get(val[i][0]) << "\t";
    //    }
    //}
    Solution solution;
    List l{ 4,2,1,3 };
    //solution.insertionSortList(l.head);
    solution.sortList(l.head);
    return 0;
}