#include<iostream>
#include<vector>
#include<list>
#include"LeetCode_array.hpp"
using namespace std;


class NumArray {
public:
    struct TreeNode {
        int sup = -1;
        int def = -1;
        int sum_val = 0;
        int lazy_sig = 0;
    };
    NumArray(vector<int>& nums) {
        int n = nums.size();
        vector<TreeNode> tmp(n);
        for (int i = 0; i < n; ++i) {
            tmp[i].sum_val = nums[i];
            tmp[i].def = tmp[i].sup = i;
        }
        tree_.emplace_back(tmp);
        while (n != 1) {
            tmp.resize(n / 2);
            vector<TreeNode>& front_layer = tree_.front();
            int i = 0;
            for (; i < n - 1; i += 2) {
                tmp[i / 2].sum_val = front_layer[i].sum_val + front_layer[i + 1].sum_val;
                tmp[i / 2].def = front_layer[i].def;
                tmp[i / 2].sup = front_layer[i + 1].sup;
            }
            if (i != n) {
                tmp.emplace_back(front_layer[i]);
                front_layer.pop_back();
            }
            n = tmp.size();
            tree_.emplace_front(tmp);
;       }

    }
    //单个结点的改变，不需要使用lazy值
    void update(int index, int val) {
        auto it = tree_.begin();
        int pre_val = 0;
        _update(index, val, it, 0, pre_val);
    }

    int sumRange(int left, int right) {
        auto it = tree_.begin();
        return _sumRange(left, right, it, 0);
    }
private:
    void _update(int idx, int val, list<vector<TreeNode>>::iterator& it, int i, int& pre_val) {
        if (it == tree_.end()) {
            return;
        }
        else if (i >= it->size()) {
            //该层没有需要修改的
            //跳转到有需要修改的层
            while (it->rbegin()->sup < idx) {
                ++it;
            }
            _update(idx, val, it, it->size() - 1, pre_val);
            return;
        }
        else if ((*it)[i].def > idx || (*it)[i].sup < idx) {
            return;
        }
        else if ((*it)[i].def == (*it)[i].sup && (*it)[i].def == idx) {
            pre_val = (*it)[i].sum_val;
            (*it)[i].sum_val = val;
            return;
        }
        else if (pre_val != 0) {
            return;
        }
        _update(idx, val, ++it, i * 2, pre_val);
        _update(idx, val, it, i * 2 + 1, pre_val);
        --it;
        (*it)[i].sum_val += val - pre_val;
    }
    void _update(int idx_left, int idx_right, int change, list<vector<TreeNode>>::iterator& it, int i) {
        if (idx_left > idx_right) {
            return;
        }
        else if (it == tree_.end()) {
            return;
        }
        else if ((*it)[i].def > idx_right || (*it)[i].sup < idx_left) {
            return;
        }
        else if ((*it)[i].def <= idx_left && (*it)[i].sup >= idx_right) {
            //完全包含
            (*it)[i].sum_val += (idx_right - idx_left + 1) * change;
            (*it)[i].lazy_sig += change;
            return;
        }
        _update(idx_left, idx_right, change, ++it, i * 2);
        _update(idx_left, idx_right, change, it, i * 2 + 1);
        --it;
    }
    int _sumRange(int left, int right, list<vector<TreeNode>>::iterator& it, int i) {
        if (i >= it->size()) {
            return 0;
        }
        int def = (*it)[i].def;
        int sup = (*it)[i].sup;
        if (it == tree_.end()) {

            return 0;
        }
        else if (def >= left && sup <= right) {
            return (*it)[i].sum_val;
        }
        else if (left > right) {
            return 0;
        }
        else if (def > right || sup < left) {
            return 0;
        }
        int a = max(left, def);
        int b = min(right, sup);
        int res = (*it)[i].lazy_sig * (b - a + 1) + _sumRange(a, b, ++it, i * 2) + _sumRange(a, b, it, i * 2 + 1);
        --it;
        return res;
    }
    list<vector<TreeNode>> tree_;
};


int main() {
    vector<int> v{ -28,-39,53,65,11,-56,-65,-39,-43,97 };
    NumArray na(v);
    na.sumRange(5, 6);
    na.update(9, 27);
    na.sumRange(2, 3);
    na.sumRange(6, 7);
    na.update(1, -82);
    na.update(3, -72);
    na.sumRange(3, 7);
    na.sumRange(1, 8);
    na.update(5, 13);
    na.update(4, -67);
    return 0;
}