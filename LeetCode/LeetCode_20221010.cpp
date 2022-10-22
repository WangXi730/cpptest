#include<iostream>
#include<unordered_map>
#include<vector>
#include<queue>
#include<set>
using namespace std;


class Solution {
public:
    static vector<int> findSubstring(string s, vector<string>& words) {
        if (words.size() > s.size()) {
            return {};
        }
        //保存每一个单词出现的次数
        unordered_map<string, int> word_count;
        //初始化word_count
        for (string& e : words) {
            word_count[e] += 1;
        }
        //每一个单词的长度
        int word_size = words[0].size();
        if (word_size > s.size()) {
            return {};
        }
        //通过vector保存每一个位置出现的单词
        vector<string> sv(s.size() - word_size + 1, "");
        //记录单词位置
        for (int i = 0; i < sv.size(); ++i) {
            string this_string(s.begin() + i, s.begin() + i + word_size);
            if (word_count.find(this_string) != word_count.end()) {
                //存在单词则记录
                sv[i] = this_string;
            }
        }
        //遍历
        vector<int> res;
        //每一次遍历的单词出现次数记录
        unordered_map<string, int> tmp_count;
        for (int i = 0; i <= sv.size() - words.size(); ++i) {
            if (sv[i] != "") {
                //有可能的开端
                int count = 1;
                ++tmp_count[sv[i]];
                for (int j = i + word_size; j < sv.size(); j += word_size) {
                    if (sv[j] == "") {
                        break;
                    }
                    else {
                        if (++tmp_count[sv[j]] <= word_count[sv[j]]) {
                            ++count;
                        }
                        else {
                            break;
                        }
                    }
                }
                if (count == words.size()) {
                    //成功找到一个字串
                    res.push_back(i);
                }
                //还原tmp_count
                tmp_count.clear();
            }
        }
        return res;
    }
};

int a = 10;
void func() {
   int a = 20;
}



int main() { 
  /*  string s = "lingmindraboofooowingdingbarrwingmonkeypoundcake";
    vector<string> v = { "fooo", "barr", "wing", "ding", "wing" };
    vector<int> res =  Solution::findSubstring(s,v);*/
    func();
    std::cout << a << std::endl;
    return 0;
}