#include<iostream>
#include<vector>
#include<set>
#include<queue>
using namespace std;



class Solution {
public:
    int flipChess(vector<string>& chessboard) {
        //�Ѽ����ܾ߱�ѡ���ֵ��λ�ã��߱���ֵ��λ�ã���ΪǱ����
        //1�����ȣ����λ��һ���ڰ��ָ���
        //2�����λ�õĳ��Ű��ӷ���һ��������1�����ӣ����Ժ���Ϊ����
        vector<pair<int, int>> potential;
        for (int i = 0; i < chessboard.size(); ++i) {
            for (int j = 0; j < chessboard[0].size(); ++j) {
                if (chessboard[i][j] == '.') {
                    //�˸���������ܾ߱�Ǳ��
                    pair<int, int> point = make_pair(i, j);
                    if (valueable(point, chessboard, '>') || valueable(point, chessboard, '<') || valueable(point, chessboard, 'A') || valueable(point, chessboard, 'V') || valueable(point, chessboard, 'F') || valueable(point, chessboard, '7') || valueable(point, chessboard, 'J') || valueable(point, chessboard, 'L')) {
                        potential.emplace_back(move(point));
                    }
                }
            }
        }
        if (potential.empty()) {
            return 0;
        }
        //����ÿ����Ǳ����λ�ã���¼��ɺ�ɫ���ӵ����ֵΪres
        int res = 0;
        for (auto& e : potential) {
            //������λ�ã����ұ�����λ��Ϊ��ɫ
            queue_.push(e);
            black_.insert(e);
            while (!queue_.empty()) {
                //ȡ��һ��λ��
                pair<int, int> point = queue_.front();
                queue_.pop();
                //ÿ�����򶼳���Ⱦɫ
                dye(point, chessboard, '>');
                dye(point, chessboard, '<');
                dye(point, chessboard, 'A');
                dye(point, chessboard, 'V');
                dye(point, chessboard, 'F');
                dye(point, chessboard, '7');
                dye(point, chessboard, 'L');
                dye(point, chessboard, 'J');
            }
            res = max(res, (int)black_.size());
            black_.clear();
        }
        return res - 1;
    }
private:
    //point�ǵ�ǰ�Ѿ�Ⱦɫ�Ľ�㣬direction�Ƿ���
    void dye(pair<int, int> point, vector<string>& chessboard, char direction) {
        //�ж��Ƿ��Ǿ��м�ֵ��λ��
        if (!valueable(point, chessboard, direction)) {
            //���߱���ֵ����û��Ⱦɫ�ı�Ҫ��ֱ���˳�
            return;
        }
        //Ⱦɫ��ʼ
        while (next_point(point, chessboard, direction)) {
            if (point_color(point, chessboard) == 'X') {
                //Ⱦɫ����
                return;
            }
            black_.insert(point);
            queue_.push(point);
        }
    }
    //�ж���һ���Ƿ�Ϊ ���м�ֵ��λ��
    bool valueable(pair<int, int> point, vector<string>& chessboard, char direction) {
        //�м�ֵ��λ������߱�����������
        //1����һ��λ��Ϊ��ɫ
        if (!next_point(point, chessboard, direction)) {
            return false;
        }
        if (point_color(point, chessboard) != 'O') {
            return false;
        }
        //2��һֱ������������ߣ����տ�����������
        while (next_point(point, chessboard, direction)) {
            switch (point_color(point, chessboard)) {
            case 'X':return true;
            case '.':return false;
            }
        }
        return false;
    }
    //��������һ����Ч�������������һ��λ�ã��������㲻������һ���㣬����false
    bool next_point(pair<int, int>& point, vector<string>& chessboard, char direction) {
        //���ſ������ǰɣ�����ľ���һ������
        switch (direction) {
        case '>': ++point.second; return point.second < chessboard[0].size();
        case '<': --point.second; return point.second >= 0;
        case 'A': --point.first; return point.first >= 0;
        case 'V': ++point.first; return point.first < chessboard.size();
        case 'F': return next_point(point, chessboard, '<') && next_point(point, chessboard, 'A');
        case '7': return next_point(point, chessboard, '>') && next_point(point, chessboard, 'A');
        case 'L': return next_point(point, chessboard, '<') && next_point(point, chessboard, 'V');
        case 'J': return next_point(point, chessboard, '>') && next_point(point, chessboard, 'V');
        }
        return false;
    }
    //�ж�������ɫ
    char point_color(pair<int, int>& point, vector<string>& chessboard) {
        if (black_.find(point) != black_.end()) {
            return 'X';
        }
        return chessboard[point.first][point.second];
    }
    set<pair<int, int>> black_;
    queue<pair<int, int>> queue_;
};


int main() {
    Solution test;
    vector<string> sv = { "....X.","....X.","XOOO..","......","......" };
    std::cout << test.flipChess(sv);
    return 0;
}