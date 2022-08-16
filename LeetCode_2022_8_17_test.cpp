#include<iostream>


using namespace std;



class Solution {
public:
    //剑指 Offer 62. 圆圈中最后剩下的数字
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
};




int main() {
    return 0;
}