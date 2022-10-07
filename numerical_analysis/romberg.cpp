#include<iostream>
#include<math.h>
using namespace std;
double fun(double x)
{
    return pow(x,2) + x;
}
double romberg(double a, double b, double(*f)(double), double eps) {
    double T1, T2, S1, S2, C1, C2, R1, R2, S, x;
    double h = b - a;
    T1 = h / 2 * ((*f)(a) + (*f)(b));
    int k = 0;
    while (1){
        S = 0;
        x = a + h / 2;
        do
        {
            S = S + (*f)(x);
            x = x + h;
        } while (x < b);
        T2 = T1 / 2 + h / 2 * S;
        S2 = T2 + 1 / 3 * (T2 - T1);
        if (k == 1)
        {
            k++;
            h = h / 2;
            T1 = T2;
            S1 = S2;
            continue;
        }
        C2 = S2 + 1 / 15 * (S2 - S1);
        if (k == 2)
        {
            k++;
            h = h / 2;
            T1 = T2;
            S1 = S2;
            C1 = C2;
            continue;
        }
        R2 = C2 + 1 / 63 * (C2 - C1);
        if (k == 3)
        {
            k++;
            h = h / 2;
            T1 = T2;
            S1 = S2;
            C1 = C2;
            R1 = R2;
            continue;
        }
        if (fabs(R2 - R1) < eps)
        {
            return R2;
        }
        k++;
        h = h / 2;
        T1 = T2;
        S1 = S2;
        C1 = C2;
        R1 = R2;
        continue;
    }

}
int main()
{
    double eps, a, b;
    cout << "请输入积分下限: " << endl;
    cin >> a;
	cout << "请输入积分下限: " << endl;
	cin >> b;
    cout << "请输入精度：" << endl;
    cin >> eps;
    double ans = romberg(a, b, *fun, eps);
    cout << ans << endl;
    return 0;
}

