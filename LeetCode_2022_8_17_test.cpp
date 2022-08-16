#include<iostream>
#include<vector>

using namespace std;



class Solution {
//��ָ Offer 62. ԲȦ�����ʣ�µ�����
public:
    int lastRemaining(int n, int m) {
        //���¶���ο�ϵ������ο�ϵʼ�������һ������Ϊ 0 ��Ԫ��
        long long res = 0;
        //i���������ڱ��л�ʣ�µ�Ԫ�أ�res�����ŵ���ɾ����Ԫ�ص��±�
        //�� i Ϊ n ��ʱ�򣬴�����Ԫ���Ѿ���ȫ�ָ���
        for (long long i = 2; i <= n; ++i) {
            res = (res - m + 1 + i * m) % i;
        }
        return n - res - 1;
    }
//��ָ Offer 63. ��Ʊ���������
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
//��ָ Offer 65. ���üӼ��˳����ӷ�
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
        //a��b����Ϊ0�����
        if ((_a < 0 && _b < 0) || (_a > 0 && _b > 0)) {
            long long t = 1;
            long long f = 0;
            if (_a < 0) {
                f = 1;
                while (f > 0) {
                    f = f << 1 | 1;
                }
                //ȥ������
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
            //ʹ��a>0���������Ǽ���a - (-b) ��
            if (_a < 0) {
                long long tmp = _a;
                _a = _b;
                _b = tmp;
            }
            //b�任����
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
            //ʹ��a > |b|����������������������
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