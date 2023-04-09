#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }
        else if (nums.size() == 1) {
            return nums[0];
        }
        else if (nums.size() == 2) {
            return max(nums[0], nums[1]);
        }
        vector<pair<int, bool>> res1(nums.size(), make_pair(0, false));
        vector<pair<int, bool>> res2(nums.size(), make_pair(0, false));
        //res1存放着拿第一个屋子的数据
        res1[0].first = nums[0];
        res1[0].second = true;
        //res2中存放着不拿第一个屋子的数据
        //接下来进行推导
        for (int i = 1; i < nums.size(); ++i) {
            //如果上一间屋子偷了，那么这间屋子的总钱就是上一间的总收益或者这件屋子内的收益+上上一间屋子的总收益
            if (res1[i - 1].second) {
                //上一间屋子的总收益
                int a = res1[i - 1].first;
                //上上一间屋子以及这间屋子的总收益
                int b = nums[i];
                if (i != 1) {
                    b += res1[i - 2].first;
                }
                if (a >= b) {
                    res1[i].first = a;
                    //那就不拿这个屋子的钱了
                    res1[i].second = false;
                }
                else if (a < b) {
                    res1[i].first = b;
                    //还是得拿这个屋子的钱
                    res1[i].second = true;
                }
            }
            //如果上一间屋子没有偷，那么最大值一定是上一间屋子的总收益+这一间屋子的钱
            else {
                res1[i].first = res1[i - 1].first + nums[i];
                res1[i].second = true;
            }
            if (res2[i - 1].second) {
                //上一间屋子的总收益
                int a = res2[i - 1].first;
                //上上一间屋子以及这间屋子的总收益
                int b = nums[i];
                if (i != 1) {
                    b += res2[i - 2].first;
                }
                if (a >= b) {
                    res2[i].first = a;
                    //那就不拿这个屋子的钱了
                    res2[i].second = false;
                }
                else if (a < b) {
                    res2[i].first = b;
                    //还是得拿这个屋子的钱
                    res2[i].second = true;
                }
            }
            //如果上一间屋子没有偷，那么最大值一定是上一间屋子的总收益+这一间屋子的钱
            else {
                res2[i].first = res2[i - 1].first + nums[i];
                res2[i].second = true;
            }
        }
        //由于res1中拿了第一个屋子的钱，所以最后一个屋子的钱必然不能动，res1[nums.size()-1]这个数据是无效的，应当比较res2[nums.size()-2]和res2[nums.size()-1]，取大者
        return max(res1[nums.size() - 2].first, res2[nums.size() - 1].first);
    }

public:
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<vector<int>> res;
        vector<int> v(k, 0);
        int sum = 1;
        for (int j = 1; j <= 9 - (k - 1); ++j) {
            sum = j;
            v[0] = j;
            if (dfs(res, v, sum, k, n, 1)) {
                return res;
            }
        }
        return res;
    }
private:
    //返回值是剪枝条件是否成立
    bool dfs(vector<vector<int>>& res, vector<int>& v, int& sum, int k, int n, int i) {
        if (sum > n) {
            return true;
        }
        if (i == k) {
            if (sum == n) {
                res.push_back(v);
                return true;
            }
            return false;
        }
        for (int j = v[i - 1] + 1; j <= 9 - (k - i - 1); ++j) {
            sum += j;
            v[i] = j;
            if (dfs(res, v, sum, k, n, i + 1)) {
                sum -= j;
                return true;
            }
            sum -= j;
        }
        return false;
    }
};

#include<map>
int main() {
    Solution test;
    //vector<int> a{ 2,3,2 };
    //test.rob(a);
    //string t = "dafsf";
    //cout << t.substr(0, 0);
    //test.combinationSum3(3,7);
    map<int, int> a;
    a[2];
    a[3];
    a[1];
    std::cout << a.rbegin()->first;
    vector<vector<int>> b;
    b.push_back({ 1,1 });
	return 0;
}
