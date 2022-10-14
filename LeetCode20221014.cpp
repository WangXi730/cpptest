#include<iostream>
#include<set>
#include<map>
#include<vector>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        if (nums.size() == 1) {
            return nums[0] == target ? 0 : -1;
        }
        //检验是否没有旋转
        if (nums[0] < nums[nums.size() - 1]) {
            //二分查找
            int left = 0;
            int right = nums.size() - 1;
            while (left < right) {
                int mid = (right + left) / 2;
                if (mid == left || mid == right) {
                    if (nums[left] == target) {
                        return left;
                    }
                    else if (nums[right] == target) {
                        return right;
                    }
                    else {
                        return -1;
                    }
                }
                if (nums[mid] < target) {
                    left = mid;
                }
                else if (nums[mid] > target) {
                    right = mid;
                }
                else {
                    return mid;
                }
            }
            return -1;
        }
        //主要算法，进行了旋转
        else {
            //改版二分查找、
            int left = 0;
            int right = nums.size() - 1;
            while (left < right) {
                int mid = (right + left) / 2;
                if (mid == left || mid == right) {
                    if (nums[left] == target) {
                        return left;
                    }
                    else if (nums[right] == target) {
                        return right;
                    }
                    else {
                        return -1;
                    }
                }
                if (nums[mid] > nums[left]) {
                    if (nums[left] > target || nums[mid] < target) {
                        left = mid;
                    }
                    else {
                        right = mid;
                    }
                }
                else if (nums[mid] < nums[left]) {
                    if (nums[right] < target || nums[mid] > target) {
                        right = mid;
                    }
                    else {
                        left = mid;
                    }
                }
                else {
                    return mid;
                }
            }
            return -1;
        }
        return -1;
    }

    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res{ -1,-1 };
        //二分查找
        int left = 0;
        int right = nums.size() - 1;
        if (nums[left] > target || nums[right] < target) {
            return res;
        }
        else if (nums[left] == target) {
            res[0] = left;
            while (left < right && nums[left] == nums[left + 1]) {
                ++left;
            }
            res[1] = left;
        }
        else if (nums[right] == target) {
            res[1] = right;
            while (left < right && nums[right] == nums[right - 1]) {
                --right;
            }
            res[0] = right;
        }
        while (left < right - 1) {
            int mid = (left + right) / 2;
            if (nums[mid] > target) {
                right = mid;
            }
            else if (nums[mid] < target) {
                left = mid;
            }
            else {
                left = mid;
                right = mid;
                while (left > 0 && nums[left] == nums[left - 1]) {
                    --left;
                }
                while (right < nums.size() && nums[right] == nums[right + 1]) {
                    ++right;
                }
                res[0] = left;
                res[1] = right;
                return res;
            }
        }
        return res;
    }
    bool isValidSudoku(vector<vector<char>>& board) {/*
        bool row[9][9];
        bool col[9][9];
        bool box[9][9];*/
        vector<vector<bool>> row(9, vector<bool>(9, true));
        vector<vector<bool>> col(9, vector<bool>(9, true));
        vector<vector<bool>> box(9, vector<bool>(9, true));
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') {
                    continue;
                }
                if (row[i][board[i][j] - 1 - '0']) {
                    row[i][board[i][j] - 1 - '0'] = false;
                }
                else {
                    return false;
                }
                if (col[j][board[i][j] - 1 - '0']) {
                    col[j][board[i][j] - 1 - '0'] = false;
                }
                else {
                    return false;
                }
                if (box[j / 3 + i / 3 * 3][board[i][j] - 1 - '0']) {
                    box[j / 3 + i / 3 * 3][board[i][j] - 1 - '0'] = false;
                }
                else {
                    return false;
                }
            }
        }
        return true;
    }
    void solveSudoku(vector<vector<char>>& board) {
        //记录可以填的数字
        vector<set<char>> row(9, { '1','2','3','4','5','6','7','8','9' });
        vector<set<char>> col(9, { '1','2','3','4','5','6','7','8','9' });
        vector<set<char>> box(9, { '1','2','3','4','5','6','7','8','9' });
        int erase_num = 0;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                char& tmp = board[i][j];
                if (tmp == '.') {
                    continue;
                }
                row[i].erase(tmp);
                col[j].erase(tmp);
                box[i / 3 * 3 + j / 3].erase(tmp);
                ++erase_num;
            }
        }
        //不断填写
        int min_num = 1;
        while (erase_num!=81) {
            int min_this = 999;
            bool need = true;
            for (int i = 0; i < 9; ++i) {
                if (row[i].empty()) {
                    continue;
                }
                for (int j = 0; j < 9; ++j) {
                    if (col[j].empty()) {
                        continue;
                    }
                    if (board[i][j] == '.') {
                        if (row[i].size() == 1) {
                            board[i][j] = *(row[i].begin());
                        }
                        else if (col[j].size() == 1) {
                            board[i][j] = *(col[j].begin());
                        }
                        else if (box[i / 3 * 3 + j / 3].size() == 1) {
                            board[i][j] = *(box[i / 3 * 3 + j / 3].begin());
                        }
                        else {
                            //查找相同的
                            set<char> st;
                            for (auto& e : row[i]) {
                                if (col[j].find(e) != col[j].end() && box[i / 3 * 3 + j / 3].find(e) != box[i / 3 * 3 + j / 3].end()) {
                                    st.insert(e);
                                }
                            }
                            if (st.size() == min_num) {
                                board[i][j] = *(st.begin());
                                min_num = 1;
                                need = false;
                            }
                            else {
                                min_this = min_this > st.size() ? st.size() : min_this;
                            }
                        }
                        if (board[i][j] != '.') {
                            //删除
                            char c = board[i][j];
                            row[i].erase(c);
                            col[j].erase(c);
                            box[i / 3 * 3 + j / 3].erase(c);
                            i = -1;
                            ++erase_num;
                            break;
                        }
                    }
                }
            }
            if (need) {
                min_num = min_this;
            }
        }
    }
};


int main() {
    //vector<int> a { 5, 7, 7, 8, 8, 10 };
    Solution test;
    //test.searchRange(a, 8);
    vector<vector<char>> board = { {'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'} };
    //test.isValidSudoku(board);
    test.solveSudoku(board);
    vector<vector<string>> sv{ {"6", "3", "9", "7", "4", "8", "1", "5", "2"},{"7", "4", "1", "6", "5", "2", "8", "3", "9"},{"8", "2", "5", "1", "3", "9", "6", "7", "4"},{"3", "5", "7", "9", "8", "6", "2", "4", "1"},{"2", "6", "4", "3", "1", "7", "5", "9", "8"},{"1", "9", "8", "5", "2", "4", "3", "6", "7"},{"9", "7", "1", "8", "6", "3", "4", "2", "5"},{"5", "8", "2", "4", "9", "1", "7", "1", "6"},{"4", "1", "6", "2", "7", "5", "9", "8", "3"} };
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cout << sv[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}