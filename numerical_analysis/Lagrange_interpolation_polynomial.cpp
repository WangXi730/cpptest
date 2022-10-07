#include<iostream>
#include<vector>
#include<cmath>
#include"Mat.hpp"

std::vector<double> Lagrange_interpolation_polynomial(Mat P){
	int m = P.row();
	int n = P.col();
	// m个点，n应该为常值2
	// 计算两两相减的矩阵
	Mat A(m);
	for(int i=0;i<m;++i){
		for(int j=0;j<m;++j){
   			A[i][j] = P[i][0]-P[j][0];
    	}
	}
	//返回值a
	std::vector<double> a(m,0.0);
	//全1的二进制序列k
	long long k = pow(2,m-1)-1;
	for(int i=0;i<m;++i){
		if(P[i][1]==0){
        	continue;
   		}
    	// 对于一个点，都有其对应的系数ci = yi/Π(xi-xj)，i~=j
    	double ci = 1.0;
		for(int j=0;j<m;++j){
    		if(i!=j){
        		ci *= A[i][j];
            }
        }
    	ci = P[i][1]/ci;
    	//计算每一个式子的结果，加到返回值里
		for(int j=0;j<=k;++j){
        	//计算每一次的结果存放到临时空间tmp里
        	double tmp = 1;
        	//每一次迭代用到的数字写作kj
        	int kj = j;
        	//记录应该存放的位置，用ki
        	int ki = 0;
        	int ni = 0;
        	while(kj){
            	ki = ki + 1;
            	if(kj%2){
                	if(ki<=i){
                    	tmp = tmp*(-P[ki-1][0]);
                    	ni = ni+1;
					}
                	else{
                    	tmp = tmp*(-P[ki][0]);
                    	ni = ni+1;
                	}
            	}
            	kj = kj/2;//整除2作为下一次迭代的数字
        	}
        	a[m-ni-1] = a[m-ni-1]+tmp*ci;
    	}
	}
	return a;
}



int main(){
	Mat P = {{M_PI/6,0.5},{M_PI/4,0.7071}};
	std::vector<double> res = Lagrange_interpolation_polynomial(P);
	for(double&d:res){
		std::cout << d << std::endl;
	}
	return 0;
}
