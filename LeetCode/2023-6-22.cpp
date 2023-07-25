#include<iostream>
#include<vector>
#include<set>
#include<queue>
using namespace std;



class Solution {
public:
    int flipChess(vector<string>& chessboard) {
        //搜集可能具备选择价值的位置，具备价值的位置，称为潜力点
        //1、首先，这个位置一定在白字附近
        //2、这个位置的朝着白子方向，一定都多于1个奕子，且以黑子为结束
        vector<pair<int, int>> potential;
        for (int i = 0; i < chessboard.size(); ++i) {
            for (int j = 0; j < chessboard[0].size(); ++j) {
                if (chessboard[i][j] == '.') {
                    //八个方向均可能具备潜力
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
        //遍历每个有潜力的位置，记录变成黑色棋子的最大值为res
        int res = 0;
        for (auto& e : potential) {
            //入队这个位置，并且标记这个位置为黑色
            queue_.push(e);
            black_.insert(e);
            while (!queue_.empty()) {
                //取出一个位置
                pair<int, int> point = queue_.front();
                queue_.pop();
                //每个方向都尝试染色
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
    //point是当前已经染色的结点，direction是方向
    void dye(pair<int, int> point, vector<string>& chessboard, char direction) {
        //判断是否是具有价值的位置
        if (!valueable(point, chessboard, direction)) {
            //不具备价值，则没由染色的必要，直接退出
            return;
        }
        //染色开始
        while (next_point(point, chessboard, direction)) {
            if (point_color(point, chessboard) == 'X') {
                //染色结束
                return;
            }
            black_.insert(point);
            queue_.push(point);
        }
    }
    //判断这一点是否为 具有价值的位置
    bool valueable(pair<int, int> point, vector<string>& chessboard, char direction) {
        //有价值的位置所需具备的两个条件
        //1、下一个位置为白色
        if (!next_point(point, chessboard, direction)) {
            return false;
        }
        if (point_color(point, chessboard) != 'O') {
            return false;
        }
        //2、一直向这个方向行走，最终可以遇到黑子
        while (next_point(point, chessboard, direction)) {
            switch (point_color(point, chessboard)) {
            case 'X':return true;
            case '.':return false;
            }
        }
        return false;
    }
    //迭代器的一个功效，将点迭代到下一个位置，如果这个点不存在下一个点，返回false
    bool next_point(pair<int, int>& point, vector<string>& chessboard, char direction) {
        //符号看不懂是吧，主打的就是一个抽象
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
    //判断奕子颜色
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