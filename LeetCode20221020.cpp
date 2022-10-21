#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include"LeetCode_array.hpp"

using namespace std;
class StackOfPlates {
public:
    StackOfPlates(int cap) : _cap(cap), stv() {
        //初始化
    }

    void push(int val) {
        if (stv.empty() || stv[stv.size() - 1].size() == _cap) {
            //需要重新申请一个栈
            stv.push_back(stack<int>());
        }
        ////优先插入靠前的栈
        //for (int i = 0; i < stv.size(); ++i) {
        //    if (stv[i].size() < _cap) {
        //        //插入
        //        stv[i].push(val);
        //        //只在一个位置插入
        //        return;
        //    }
        //}
        stv[stv.size() - 1].push(val);
    }

    int pop() {
        //判断是否没有元素
        if (stv.empty()) {
            return -1;
        }
        //弹出的元素应该是最后一个栈的最后的元素
        while (stv[stv.size() - 1].size() == 0) {
            //弹出最后一个栈
            stv.pop_back();
        }
        //弹出元素并返回
        int res = stv[stv.size() - 1].top();
        stv[stv.size() - 1].pop();
        while (!stv.empty()&&stv[stv.size() - 1].size() == 0) {
            stv.pop_back();
        }
        return res;
    }

    int popAt(int index) {
        if (stv.empty()) {
            return -1;
        }
        //删除不存在元素的栈
        while (stv[stv.size() - 1].size() == 0) {
            stv.pop_back();
        }
        //如果栈不存在，则返回-1
        if (stv.size() <= index) {
            return -1;
        }
        //弹出并返回
        int res = stv[index].top();
        stv[index].pop();
        if (stv[index].size() == 0) {
            for (int i = index; i < stv.size() - 1; ++i) {
                stv[i] = move(stv[i + 1]);
            }
            stv.pop_back();
        }
        return res;
    }
    int _cap;
    vector<stack<int>> stv;
    int trap(std::vector<int>& vec) {
        int result = 0;
        // TODO:
        int n = vec.size();
        for (int i = 0; i < n - 1; ++i) {
            if (vec[i] <= vec[i + 1]) {
                continue;
            }
            int right = -1;
            for (int j = i + 1; j < n; ++j) {
                if (vec[j] >= vec[i]) {
                    right = j;
                    break;
                }
                else if (right == -1 || vec[j] >= vec[right]) {
                    right = j;
                }
            }
            if (right == -1) {
                break;
            }
            int high = vec[i] > vec[right] ? vec[right] : vec[i];
            for (int j = i + 1; j < right; ++j) {
                result += high - vec[j];
            }
            i = right - 1;
        }
        return result;
    }


};

/**
 * Your StackOfPlates object will be instantiated and called as such:
 * StackOfPlates* obj = new StackOfPlates(cap);
 * obj->push(val);
 * int param_2 = obj->pop();
 * int param_3 = obj->popAt(index);
 */

class AnimalShelf {
public:
    AnimalShelf() {

    }

    void enqueue(vector<int> animal) {
        //如果两个队列都是空，插入时间设置为 0 
        if (_q[0].empty() && _q[1].empty()) {
            _q[animal[1]].push(make_pair(animal[0], 0));
        }
        else if (_q[0].empty()) {
            _q[animal[1]].push(make_pair(animal[0], _q[1].back().second + 1));
        }
        else if (_q[1].empty()) {
            _q[animal[1]].push(make_pair(animal[0], _q[0].back().second + 1));
        }
        else {
            _q[animal[1]].push(make_pair(animal[0], max(_q[0].back().second, _q[1].back().second) + 1));
        }
    }

    vector<int> dequeueAny() {
        if (_q[0].empty() && _q[1].empty()) {
            return { -1,-1 };
        }
        else if (_q[0].empty()) {
            pair<int, int> res = _q[1].front();
            _q[1].pop();
            return { res.first,1 };
        }
        else if (_q[1].empty()) {
            pair<int, int> res = _q[0].front();
            _q[0].pop();
            return { res.first,0 };
        }
        else {
            pair<int, int> res;
            int res2;
            if (_q[0].front().second < _q[1].front().second) {
                res = _q[0].front();
                _q[0].pop();
                res2 = 0;
            }
            else {
                res = _q[1].front();
                _q[1].pop();
                res2 = 1;
            }
            return { res.first,res2 };
        }
        return { -1,-1 };
    }

    vector<int> dequeueDog() {
        if (_q[1].empty()) {
            return { -1,-1 };
        }
        int res = _q[1].front().first;
        _q[1].pop();
        return { res,1 };
    }

    vector<int> dequeueCat() {
        if (_q[0].empty()) {
            return { -1,-1 };
        }
        int res = _q[0].front().first;
        _q[0].pop();
        return { res,0 };
    }
//private:
    queue<pair<int, int>> _q[2];//<编号，时间>
};

/**
 * Your AnimalShelf object will be instantiated and called as such:
 * AnimalShelf* obj = new AnimalShelf();
 * obj->enqueue(animal);
 * vector<int> param_2 = obj->dequeueAny();
 * vector<int> param_3 = obj->dequeueDog();
 * vector<int> param_4 = obj->dequeueCat();
 */

/**
 * Your AnimalShelf object will be instantiated and called as such:
 * AnimalShelf* obj = new AnimalShelf();
 * obj->enqueue(animal);
 * vector<int> param_2 = obj->dequeueAny();
 * vector<int> param_3 = obj->dequeueDog();
 * vector<int> param_4 = obj->dequeueCat();
 */
int main() {
    /*StackOfPlates sop(3);
    vector<string> operation = {  "pop", "popAt", "push", "popAt", "popAt", "pop", "pop", "push", "popAt", "pop", "push", "push", "pop", "popAt", "popAt", "push", "push", "push", "popAt", "pop", "pop", "pop", "popAt", "pop", "push", "popAt", "push", "push", "popAt", "push", "push", "pop", "popAt", "push", "pop", "popAt", "push", "pop", "push", "pop", "popAt", "popAt", "pop", "push", "push", "pop", "popAt", "push", "push", "pop", "pop", "popAt" };
    vector<vector<int>> data = {  {}, {1}, {1}, {2}, {2}, {}, {}, {9}, {3}, {}, {51}, {20}, {}, {2}, {0}, {35}, {1}, {19}, {3}, {}, {}, {}, {1}, {}, {36}, {1}, {19}, {3}, {3}, {15}, {44}, {}, {3}, {46}, {}, {0}, {42}, {}, {31}, {}, {0}, {2}, {}, {10}, {49}, {}, {1}, {14}, {50}, {}, {}, {3} };
    for (int i = 0; i < operation.size(); ++i) {
        if (operation[i] == "push") {
            sop.push(data[i][0]);
            std::cout << std::endl;
        }
        else if (operation[i] == "pop") {
            int res = sop.pop();
            std::cout << res << std::endl;
        }
        else if (operation[i] == "popAt") {
            int res = sop.popAt(data[i][0]);
            std::cout << res << endl;
        }
    }*/
    //string s = "[[], [[0, 0]], [[1, 1]], [[2, 0]], [[3, 0]], [[4, 0]], [[5, 0]], [[6, 0]], [[7, 0]], [[8, 0]], [[9, 0]], [[10, 0]], [[11, 1]], [[12, 1]], [[13, 0]], [[14, 0]], [[15, 0]], [[16, 0]], [[17, 1]], [[18, 0]], [[19, 0]], [[20, 1]], [[21, 1]], [[22, 1]], [[23, 1]], [[24, 0]], [[25, 0]], [[26, 0]], [[27, 1]], [[28, 1]], [[29, 1]], [[30, 1]], [[31, 0]], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], [], []] ";
    //array_to_c(s);
    //std::cout << s;
    vector<string> sv = { "AnimalShelf", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "enqueue", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny", "dequeueAny"};
    vector<vector<int>> vv = { {}, {{0, 0}}, {{1, 1}}, {{2, 0}}, {{3, 0}}, {{4, 0}}, {{5, 0}}, {{6, 0}}, {{7, 0}}, {{8, 0}}, {{9, 0}}, {{10, 0}}, {{11, 1}}, {{12, 1}}, {{13, 0}}, {{14, 0}}, {{15, 0}}, {{16, 0}}, {{17, 1}}, {{18, 0}}, {{19, 0}}, {{20, 1}}, {{21, 1}}, {{22, 1}}, {{23, 1}}, {{24, 0}}, {{25, 0}}, {{26, 0}}, {{27, 1}}, {{28, 1}}, {{29, 1}}, {{30, 1}}, {{31, 0}}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {}, {} };
    AnimalShelf as;
    for (int i = 0; i < sv.size(); ++i) {
        if (sv[i] == "enqueue") {
            as.enqueue(vv[i]);
        }
        else if (sv[i] == "dequeueCat") {
            vector<int> tmp =  as.dequeueCat();
            std::cout << tmp[0] << " " << tmp[1] << std::endl;
        }
        else if (sv[i] == "dequeueDog") {
            vector<int> tmp = as.dequeueDog();
            std::cout << tmp[0] << " " << tmp[1] << std::endl;
        }
        else if (sv[i] == "dequeueAny") {
            vector<int> tmp = as.dequeueAny();
            std::cout << tmp[0] << " " << tmp[1] << std::endl;
        }
    }
    return 0;
}