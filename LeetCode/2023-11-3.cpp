#include"LeetCodeTools.hpp"


leetcode

class LFUCache {
public:
    LFUCache(int capacity) : capacity_(capacity) {

    }

    int get(int key) {
        auto e = key_node_m_.find(key);
        if (e == key_node_m_.end()) {
            return -1;
        }
        compare_.erase(e->second);
        e->second->times += 1;
        e->second->time = time_++;
        compare_.insert(e->second);
        return e->second->value;
    }

    void put(int key, int value) {
        auto e = key_node_m_.find(key);
        if (e == key_node_m_.end()) {
            //检查容器容量
            if (key_node_m_.size() == capacity_) {
                //删除一个
                auto del = compare_.begin();
                key_node_m_.erase((*del)->key);
                Node* p = *del;
                compare_.erase(del);
                delete p;
            }
            //插入新来的
            Node* p = new Node;
            p->times = 0;
            p->time = time_++;
            p->key = key;
            p->value = value;
            key_node_m_[key] = p;
            compare_.insert(p);
        }
        else {
            //之前就有，那就改变一下值就行
            compare_.erase(e->second);
            e->second->times += 1;
            e->second->time = time_++;
            e->second->value = value;
            compare_.insert(e->second);
        }
    }
private:
    struct Node {
        int times;
        int key;
        int value;
        int time;
    };
    struct myLess {
        template<class A>
        bool operator()(const A& a, const A& b)const {
            if (a->times == b->times) {
                return a->time < b->time;
            }
            return a->times < b->times;
        }
    };
    map<int, Node*> key_node_m_;
    set<Node*, myLess> compare_;
    int capacity_;
    int time_ = 0;
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

#include<fstream>

int main() {
    ifstream ifs;
    ifs.open("C:\\git\\cpptest\\LeetCode\\test.txt",ios::in);
    string test;
    ifs >> test;
    ifs.close();
    ifs.open(R"(C:\git\cpptest\LeetCode\data.txt)", ios::in);
    string data;
    ifs >> data;
    ifs.close();
    vector<string> vs;
    vector<vector<int>> vv;
    wx::create(test, vs);
    wx::create(data, vv);
    LFUCache lfu(vv[0][0]);
    for (int i = 1; i < vs.size(); ++i) {
        if (vs[i] == "put") {
            lfu.put(vv[i][0], vv[i][1]);
        }
        else if (vs[i] == "get") {
            lfu.get(vv[i][0]);
        }
    }


    return 0;
}