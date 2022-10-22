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
        //����ÿһ�����ʳ��ֵĴ���
        unordered_map<string, int> word_count;
        //��ʼ��word_count
        for (string& e : words) {
            word_count[e] += 1;
        }
        //ÿһ�����ʵĳ���
        int word_size = words[0].size();
        if (word_size > s.size()) {
            return {};
        }
        //ͨ��vector����ÿһ��λ�ó��ֵĵ���
        vector<string> sv(s.size() - word_size + 1, "");
        //��¼����λ��
        for (int i = 0; i < sv.size(); ++i) {
            string this_string(s.begin() + i, s.begin() + i + word_size);
            if (word_count.find(this_string) != word_count.end()) {
                //���ڵ������¼
                sv[i] = this_string;
            }
        }
        //����
        vector<int> res;
        //ÿһ�α����ĵ��ʳ��ִ�����¼
        unordered_map<string, int> tmp_count;
        for (int i = 0; i <= sv.size() - words.size(); ++i) {
            if (sv[i] != "") {
                //�п��ܵĿ���
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
                    //�ɹ��ҵ�һ���ִ�
                    res.push_back(i);
                }
                //��ԭtmp_count
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