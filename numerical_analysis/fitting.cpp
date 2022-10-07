#include<iostream>
#include<vector>
#include"Mat.hpp"

std::vector<double> Ols(std::vector<double> x, std::vector<double> y,std::vector<double> w,int k){
	// x是自变量，y是对应函数值，w是权重系数，k是次数
	// 矩阵A是加权内积矩阵
	std::vector<double> f(k+1,0.0);
	// f 是返回值，f(i) 为 返回的多项式的 i 次系数
	//构造 k+1 阶全 0 矩阵
	Mat A(k+1);
	int n = x.size();
	//有n个数据
	for(int i=0;i<=k;++i){
    	//对角线元素
    	for(int t=0;t<n;++t){
			double tmp = 1;
			for(int it=0;it<i;++it){
				tmp*=x[t];
			}
   			A[i][i] = A[i][i] + w[t]*tmp;
    	}
		for(int j=i+1;j<k+1;++j){
        	//非对角线元素
			for(int t=0;t<n;++t){
				double tmp = 1;
				for(int it=0;it<i+j;++it){
					tmp *= x[t];
				}
       			A[i][j] = A[i][j] + w[t]*tmp;
            }
        	//对称
        	A[j][i] = A[i][j];
        }
   	}
	//右端向量b
	std::vector<double> b(k+1,0.0);
	for(int i=0;i<k+1;++i){
		for(int t=0;t<n;++t){
			double tmp = 1;
			for(int it=0;it<i;++it){
				tmp *= x[t];
			}
    		b[i] = w[t]*y[t]*tmp+b[i];
    	}
	}
	f = A.inv()*b;
	return f;
}


	
int main(){
	//测试
	std::vector<double> x = {-3,-1,1,3};
	std::vector<double> y = {15,5,1,5};
	std::vector<double> f = Ols(x,y,{1.0,1.0,1.0,1.0},2);
	std::cout << f[2] << "x² + " << f[1] << "x + " << f[0] << std::endl;
	return 0;
}
