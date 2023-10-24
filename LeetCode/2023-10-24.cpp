#include"LeetCodeTools.hpp"

leetcode

class Solution {
public:
    int numRollsToTarget(int n, int k, int target) {
        vector<vector<long long>> dp(target + 1, vector<long long>(n + 1, 0));
        //n个骰子，k面，目标target的数量 = for(ki:k) n-1个投资，k面，目标为target-ki的和
        //0个骰子和target为0时，有一种情况
        dp[0][0] = 1;
        for (int i = 1; i <= target; ++i) {
            //i是当前的target
            for (int j = 1; j <= n; ++j) {
                //j是当前的骰子数量
                for (int ki = 1; ki <= k; ++ki) {
                    if (i - ki >= 0) {
                        dp[i][j] += dp[i - ki][j - 1];
                        dp[i][j] %= 1000000007;
                    }
                    else {
                        break;
                    }
                }
            }
        }
        return (int)dp[target][n];
    }
public:
    int sumDistance(vector<int>& nums, string s, int d) {
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'L') {
                nums[i] -= d;
            }
            else {
                nums[i] += d;
            }
        }
        long long res = 0;
        sort(nums.begin(), nums.end());
        for (int i = 1; i < n; ++i) {
            res += abs((n - i) * i * ((long long)nums[i] - nums[i - 1]) % 1000000007);
            res %= 1000000007;
        }
        return res;
    }
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.size() == 1) {
            return max(0, -prices[0]);
        }
        int n = prices.size();
        vector<vector<pair<int, int>>> dp(k, vector<pair<int, int>>(n));//每一个dp[i]都是一个v，代表着完成了i次交易的最大值
        //初始化没有完成第一笔交易
        dp[0][0].first = -prices[0];
        //初始化完成了第一笔交易的
        dp[0][0].second = 0;
        for (int i = 1; i < n; ++i) {
            dp[0][i].first = max(dp[0][i - 1].first, -prices[i]);
            //要完成第一笔交易，可以选择之前完成的结果，也可以选择在当天完成
            dp[0][i].second = max(dp[0][i - 1].second, dp[0][i - 1].first + prices[i]);
        }
        //根据第一行，完成dp初始化
        for (int i = 1; i < k; ++i) {
            //初始化第一个元素
            //可以选择购买，但今天无法完成抛售
            dp[i][i].first = dp[i - 1][i - 1].second - prices[i];
            for (int j = i + 1; j < n; ++j) {
                //如果在第j天需要完成购买，可以是之前已经完成了，也可以当天完成
                dp[i][j].first = max(dp[i][j - 1].first, dp[i - 1][j - 1].second - prices[j]);
                //如果在第j天完成第i次抛售，可以是之前已经完成，也可以当天抛售
                dp[i][j].second = max(dp[i][j - 1].second, dp[i][j - 1].first + prices[j]);
            }
        }
        //从众多结果中，选取最大的一个
        int res = 0;
        for (int i = 0; i < k; ++i) {
            res = max(res, max(dp[i][n - 1].first, dp[i][n - 1].second));
        }
        return res;
    }
public:
    int maxProfit(vector<int>& prices, int fee) {
        int n = prices.size();
        vector<pair<int, int>> dp(n);
        //first是当前持有股票的最大盈利，second是不持有
        dp[0].first = -prices[0];
        for (int i = 1; i < n; ++i) {
            //如果之前就持有股票，或者现在购买股票，那么今天就可以持有股票
            dp[i].first = max(dp[i - 1].second - prices[i], dp[i - 1].first);
            //如果抛售现在持有的股票，或者本身就不持有股票，那么今天就可以不持有股票了
            dp[i].second = max(dp[i - 1].first - fee + prices[i], dp[i - 1].second);
        }
        return max(dp[n - 1].first, dp[n - 1].second);
    }
};

class StockSpanner {
public:
    StockSpanner() {
    }

    int next(int price) {
        while (!st.empty() && st.top().first <= price) {
            st.pop();
        }
        if (st.empty()) {
            st.push(make_pair(price,i++));
            return i;
        }
        int res = i - st.top().second;
        st.push(make_pair(price, i++));
        return res;
    }
private:
    stack<pair<int, int>> st;
    int i = 0;
};

int main() {
    Solution test;/*
    cout << test.numRollsToTarget(30,30,500) << endl;*/
    vector<int> nums;
    wx::create("[-10,-13,10,14,11]", nums);
    string s = "LRLLR";
    int d = 2;
    //cout << test.sumDistance(nums,s,d) << endl;
    vector<int> p = { 3,2,6,5,0,3 };
    test.maxProfit(2,p);

    vector<int> p2 = { 1, 3, 7, 5, 10, 3 };
    test.maxProfit(p2, 3);

    StockSpanner ss;
    vector<int> arr{ 31,41,48,50,79 };
    for (int i = 0; i < arr.size(); ++i) {
        cout << ss.next(arr[i]) << endl;
    }
    return 0;
}