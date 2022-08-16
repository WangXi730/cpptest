#include<iostream>
#include<vector>

using namespace std;



class Solution {
//剑指 Offer 62. 圆圈中最后剩下的数字
public:
    int lastRemaining(int n, int m) {
        //重新定义参考系，这个参考系始终以最后一个点作为 0 号元素
        long long res = 0;
        //i代表着现在表中还剩下的元素，res代表着当下删除的元素的下标
        //当 i 为 n 的时候，代表着元素已经完全恢复了
        for (long long i = 2; i <= n; ++i) {
            res = (res - m + 1 + i * m) % i;
        }
        return n - res - 1;
    }
//剑指 Offer 63. 股票的最大利润
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) {
            return 0;
        }
        vector<maxProfit_struct> profit;
        profit.push_back(maxProfit_struct(prices[0], prices[0]));
        for (int i = 1; i < prices.size(); ++i) {
            profit.push_back(maxProfit_struct(prices[i], profit[i - 1].Min()));
        }
        int res = profit[0].Profit();
        for (int i = 1; i < profit.size(); ++i) {
            if (profit[i].Profit() > res) {
                res = profit[i].Profit();
            }
        }
        return res;
    }
private:
    struct maxProfit_struct {
        maxProfit_struct(int v, int p) :val(v), pre_min(p) {}
        int Min() {
            return min(val, pre_min);
        }
        int Profit() {
            return val - pre_min;
        }
        int val;
        int pre_min;
    };
//剑指 Offer 65. 不用加减乘除做加法
public:
    int add(int a, int b) {
        if (a == 0) {
            return b;
        }
        else if (b == 0) {
            return a;
        }
        long long _a = a;
        long long _b = b;
        //a，b均不为0的情况
        if ((_a < 0 && _b < 0) || (_a > 0 && _b > 0)) {
            long long t = 1;
            long long f = 0;
            if (_a < 0) {
                f = 1;
                while (f > 0) {
                    f = f << 1 | 1;
                }
                //去除符号
                _a = _a ^ f;
                _b = _b ^ f;
                long long tmp = 1;
                while ((_a & tmp) != 0) {
                    _a ^= tmp;
                    tmp <<= 1;
                }
                _a |= tmp;
                tmp = 1;
                while ((_b & tmp) != 0) {
                    _b ^= tmp;
                    tmp <<= 1;
                }
                _b |= tmp;
            }
            while (_b) {
                if (_b % 2 == 1) {
                    long long tmp = t;
                    while ((_a & tmp) != 0) {
                        _a = _a ^ tmp;
                        tmp <<= 1;
                    }
                    _a = _a | tmp;
                }
                _b >>= 1;
                t <<= 1;
            }
            if (f < 0) {
                _a ^= f;
                t = 1;
                while ((_a & t) != 0) {
                    _a ^= t;
                    t <<= 1;
                }
                _a = _a | t;
            }
        }
        else {
            //使得a>0，这样就是计算a - (-b) 了
            if (_a < 0) {
                long long tmp = _a;
                _a = _b;
                _b = tmp;
            }
            //b变换符号
            long long f = 1;
            while (f > 0) {
                f = f << 1 | 1;
            }
            _b = _b ^ f;
            long long tmp = 1;
            while ((_b & tmp) != 0) {
                _b ^= tmp;
                tmp <<= 1;
            }
            _b |= tmp;
            //使得a > |b|，这样减下来就是正数了
            if (_a > _b) {
                f = 0;
            }
            else {
                long long tmp = _a;
                _a = _b;
                _b = tmp;
            }
            long long t = 1;
            while (_b) {
                if (_b % 2 == 1) {
                    tmp = t;
                    while ((tmp & _a) == 0) {
                        _a = _a | tmp;
                        tmp <<= 1;
                    }
                    _a = _a ^ tmp;
                }
                _b >>= 1;
                t <<= 1;
            }
            if (f < 0) {
                _a ^= f;
                t = 1;
                while ((_a & t) != 0) {
                    _a ^= t;
                    t <<= 1;
                }
                _a = _a | t;
            }
        }
        return _a;
    }
};




int main() {
    Solution a;
    a.add(-2147483648,1);
    
    //for (int i = 0; i < 10; ++i) {
    //    cout << (i ^ -1 ) << endl;
    //}
    return 0;
}