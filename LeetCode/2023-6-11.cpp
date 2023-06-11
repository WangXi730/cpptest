#include<iostream>
#include<stack>
#include<vector>
#include<set>
using namespace std;
class DinnerPlates {
public:
    DinnerPlates(int capacity) {
        capacity_ = capacity;
    }

    void push(int val) {
        //保证有未满的盘子
        if (unfull_set.empty()) {
            st_v.push_back(stack<int>());
            unfull_set.insert(st_v.size() - 1);
        }
        //放入第一个未满的盘子
        auto it = unfull_set.begin();
        st_v[*it].push(val);
        //记录这个盘子非空
        unnull_set.insert(*it);
        //如果满了，从未满集合移除
        if (st_v[*it].size() >= capacity_) {
            unfull_set.erase(it);
        }
    }

    int pop() {
        if (unnull_set.empty()) {
            return -1;
        }
        //取出最大的数字
        auto it = unnull_set.end();
        --it;
        int res = st_v[*it].top();
        st_v[*it].pop();
        //记录未满
        unfull_set.insert(* it);
        //如果空了，从非空集合移除
        if (st_v[*it].empty()) {
            unnull_set.erase(*it);
        }
        return res;
    }

    int popAtStack(int index) {
        if (index >= st_v.size()) {
            return -1;
        }
        if (st_v[index].empty()) {
            return -1;
        }
        int res = st_v[index].top();
        st_v[index].pop();
        //跟新未满集合
        unfull_set.insert(index);
        //如果空了，从非空集合中移除
        if (st_v[index].empty()) {
            unnull_set.erase(index);
        }
        return res;
    }
    int capacity_ = 0;
    vector<stack<int>> st_v;
    set<int> unfull_set;//未满盘子集合
    set<int> unnull_set;//非空盘子集合

};

/**
 * Your DinnerPlates object will be instantiated and called as such:
 * DinnerPlates* obj = new DinnerPlates(capacity);
 * obj->push(val);
 * int param_2 = obj->pop();
 * int param_3 = obj->popAtStack(index);
 */

int main() {
    DinnerPlates D = DinnerPlates(2);  // 初始化，栈最大容量 capacity = 2
    D.push(1);
    D.push(2);
    D.push(3);
    D.push(4);
    D.push(7);         // 栈的现状为：    2  4
        D.popAtStack(8);   // 返回 2。栈的现状为：      4
        D.push(20);        // 栈的现状为：  20  4
        D.push(21);        // 栈的现状为：  20  4 21
        D.popAtStack(0);   // 返回 20。栈的现状为：       4 21
        D.popAtStack(2);   // 返回 21。栈的现状为：       4
        D.pop();            // 返回 5。栈的现状为：        4
        D.pop();           // 返回 4。栈的现状为：    1  3 
        D.pop();          // 返回 3。栈的现状为：    1 
        D.pop();           // 返回 1。现在没有栈。
        D.pop();           // 返回 -1。仍然没有栈。

    
    return 0;
}