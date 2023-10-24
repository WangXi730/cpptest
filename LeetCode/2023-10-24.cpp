#include"LeetCodeTools.hpp"

leetcode

class Solution {
public:
    int numRollsToTarget(int n, int k, int target) {
        vector<vector<long long>> dp(target + 1, vector<long long>(n + 1, 0));
        //n�����ӣ�k�棬Ŀ��target������ = for(ki:k) n-1��Ͷ�ʣ�k�棬Ŀ��Ϊtarget-ki�ĺ�
        //0�����Ӻ�targetΪ0ʱ����һ�����
        dp[0][0] = 1;
        for (int i = 1; i <= target; ++i) {
            //i�ǵ�ǰ��target
            for (int j = 1; j <= n; ++j) {
                //j�ǵ�ǰ����������
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
        vector<vector<pair<int, int>>> dp(k, vector<pair<int, int>>(n));//ÿһ��dp[i]����һ��v�������������i�ν��׵����ֵ
        //��ʼ��û����ɵ�һ�ʽ���
        dp[0][0].first = -prices[0];
        //��ʼ������˵�һ�ʽ��׵�
        dp[0][0].second = 0;
        for (int i = 1; i < n; ++i) {
            dp[0][i].first = max(dp[0][i - 1].first, -prices[i]);
            //Ҫ��ɵ�һ�ʽ��ף�����ѡ��֮ǰ��ɵĽ����Ҳ����ѡ���ڵ������
            dp[0][i].second = max(dp[0][i - 1].second, dp[0][i - 1].first + prices[i]);
        }
        //���ݵ�һ�У����dp��ʼ��
        for (int i = 1; i < k; ++i) {
            //��ʼ����һ��Ԫ��
            //����ѡ���򣬵������޷��������
            dp[i][i].first = dp[i - 1][i - 1].second - prices[i];
            for (int j = i + 1; j < n; ++j) {
                //����ڵ�j����Ҫ��ɹ��򣬿�����֮ǰ�Ѿ�����ˣ�Ҳ���Ե������
                dp[i][j].first = max(dp[i][j - 1].first, dp[i - 1][j - 1].second - prices[j]);
                //����ڵ�j����ɵ�i�����ۣ�������֮ǰ�Ѿ���ɣ�Ҳ���Ե�������
                dp[i][j].second = max(dp[i][j - 1].second, dp[i][j - 1].first + prices[j]);
            }
        }
        //���ڶ����У�ѡȡ����һ��
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
        //first�ǵ�ǰ���й�Ʊ�����ӯ����second�ǲ�����
        dp[0].first = -prices[0];
        for (int i = 1; i < n; ++i) {
            //���֮ǰ�ͳ��й�Ʊ���������ڹ����Ʊ����ô����Ϳ��Գ��й�Ʊ
            dp[i].first = max(dp[i - 1].second - prices[i], dp[i - 1].first);
            //����������ڳ��еĹ�Ʊ�����߱���Ͳ����й�Ʊ����ô����Ϳ��Բ����й�Ʊ��
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