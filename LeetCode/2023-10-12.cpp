#include"LeetCodeTools.hpp"

using namespace std;


class Solution {
public:
    vector<int> topStudents(vector<string>& positive_feedback, vector<string>& negative_feedback, vector<string>& report, vector<int>& student_id, int k) {
        int student_count = student_id.size();
        unordered_set<string> positive_set;
        unordered_set<string> negative_set;
        for (int i = 0; i < negative_feedback.size(); ++i) {
            negative_set.insert(negative_feedback[i]);
        }
        for (int i = 0; i < positive_feedback.size(); ++i) {
            positive_set.insert(positive_feedback[i]);
        }
        //计算得分
        vector<int> score(student_count, 0);
        for (int i = 0; i < student_count; ++i) {
            int index = 0;
            while (index < report[i].size()) {
                //找到下一个位置
                int e = report[i].find(' ', index);
                if (e == string::npos) {
                    e = report[i].size();
                }
                //查找这个单词
                if (positive_set.find(report[i].substr(index, e - index)) != positive_set.end()) {
                    //正面
                    score[i] += 3;
                }
                else if (negative_set.find(report[i].substr(index, e - index)) != negative_set.end()) {
                    //负面
                    score[i] -= 1;
                }
                //迭代单词
                index = e + 1;
            }
        }
        //排名
        vector<int> res(student_count);
        for (int i = 1; i < student_count; ++i) {
            res[i] = res[i - 1] + 1;
        }
        sort(res.begin(), res.end(), [&](int a, int b)->bool {
            if (score[a] == score[b]) {
                return student_id[a] < student_id[b];
            }
            return score[a] > score[b];
            });
        res.resize(k);
        for (int i = 0; i < res.size(); ++i) {
            res[i] = student_id[res[i]];
        }
        return res;
    }
};



int main() {
    vector<string> positive_feedback;
    vector<string> negative_feedback;
    vector<string> report;
    vector<int> student_id;
    int k;
    wx::create(R"(["fkeofjpc","qq","iio"])", positive_feedback);
    wx::create(R"(["jdh","khj","eget","rjstbhe","yzyoatfyx","wlinrrgcm"])", negative_feedback);
    wx::create(R"(["rjstbhe eget kctxcoub urrmkhlmi yniqafy fkeofjpc iio yzyoatfyx khj iio","gpnhgabl qq qq fkeofjpc dflidshdb qq iio khj qq yzyoatfyx","tizpzhlbyb eget z rjstbhe iio jdh jdh iptxh qq rjstbhe","jtlghe wlinrrgcm jnkdbd k iio et rjstbhe iio qq jdh","yp fkeofjpc lkhypcebox rjstbhe ewwykishv egzhne jdh y qq qq","fu ql iio fkeofjpc jdh luspuy yzyoatfyx li qq v","wlinrrgcm iio qq omnc sgkt tzgev iio iio qq qq","d vhg qlj khj wlinrrgcm qq f jp zsmhkjokmb rjstbhe"])", report);
    wx::create(R"([96537918,589204657,765963609,613766496,43871615,189209587,239084671,908938263])", student_id);
    wx::create(R"(3)", k);
    Solution test;
    test.topStudents(positive_feedback, negative_feedback, report, student_id, k);

    return 0;
}