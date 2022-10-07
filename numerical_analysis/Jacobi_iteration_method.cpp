#include<iostream>
#include<cmath>
#include"Mat.hpp"

//向量的无穷范数
double norm(std::vector<double>& x){
	double res = 0;
	for(double&i:x){
		if(fabs(i)>res){
			res = fabs(i);
		}
	}
	return res;
}
//矩阵的无穷范数
double norm(Mat& m){
	std::vector<double> x(m.row(),0.0);
	for(int i=0;i<m.col();++i){
		for(int j=0;j<m.row();++j){
			x[j] += fabs(m[j][i]);
		}
	}
	return norm(x);
}

//Jacobi迭代法
std::vector<double> J_function(Mat& M, std::vector<double>& g, double w){
	int m = M.row();
	int n = M.col();
	//计算第一次迭代的结果x1
	std::vector<double> x(m,0.0);
	std::vector<double> x1 = M * x;
	for(int j=0;j<g.size();++j){
		x1[j] += g[j];
	}
	//计算迭代次数k，范数选择无穷范数
	double tmp1 = norm(x1);
	double tmp2 = norm(M);
	
	int k = (int)(log((w*(1-tmp2))/tmp1)/log(tmp2)) + 1;
	//开始迭代
	for(int i=0;i<k;++i){
    	x = M*x;
		for(int j=0;j<g.size();++j){
			x[j] += g[j];
		}
	}
	return x;
}

int main(){
	Mat M = {{    0,-4.0/14,-4.0/14,-4.0/14},
	    	 {-4.0/14,    0,-4.0/14,-4.0/14},
    		 {-4.0/14,-4.0/14,    0,-4.0/14},
    		 {-4.0/14,-4.0/14,-4.0/14,    0}};
	std::vector<double> g = {-4.0/14.0,16.0/14.0,36.0/14.0,56.0/14.0};
    std::vector<double> x = J_function(M,g,0.000001);
	for(int i=0;i<x.size();++i){
		std::cout << x[i] << "\t";
	}
	std::cout << std::endl;
	return 0;
}
