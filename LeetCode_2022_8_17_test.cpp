#include<iostream>


using namespace std;



class Solution {
public:
    //��ָ Offer 62. ԲȦ�����ʣ�µ�����
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
};




int main() {
    return 0;
}