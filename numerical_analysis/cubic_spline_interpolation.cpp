#include<iostream>
#include<vector>
#include"Mat.hpp"

std::vector<double> Hermite3(std::vector<double> x, std::vector<double> y, std::vector<double> y1){
	// x表示插值两点的自变量
	// y表示对应的函数值
	// y1表示一次导数
	//f(i)表示i-1次的系数
	std::vector<double> f(4);
	double h = x[2] - x[1];
	f[3] = 2*(y[0]-y[1])/(h*h*h) + (y1[0]+y1[1])/(h*h);
	f[2] = (x[1]-3*x[0])*y[0]-4*x[1]*y[0]+(3*x[1]-x[0])*y[1]+4*x[0]*y[1])/(h*h*h)+((-x[0]-2*x[1])*y1[0]+(-x[1]-2*x[0])*y1[1])/(h*h);
	f[1] = (y[0]*(2*x[1]*x[1])-2*(x[1]-3*x[0])*x[1])+y[1]*(-2*x[0]*x[0]-2*x[0]*(3*x[1]-x[0]))/(h*h*h)+(y1[0]*(x[1]*x[1]+2*x[0]*x[1])+y1[1]*(x[0]*x[0]+2*x[0]*x[1]))/(h*h);
	f[0] = (y[0]*x[1]*x[1]*(x[1]-3*x[0])+y[1]*x[0]*x[0]*(3*x[1]-x[0]))/(h*h*h) + (-x[0]*x[1]*x[1]*y1[0]-x[1]*x[0]*x[0]*y1[1])/(h*h);
	return f;
}

//三转角法
Mat Three_corner_method(std::vector<double> x, std::vector<double> y0, std::vector<double> y1){
	// x表示对应x的取值
	// y0表示y的取值
	// y1表示x在a,b上的一阶导数
	int col = x.size();
	//行有了，因为是方阵，列跟行应该相等
	int row = col;
	//构造矩阵
	Mat A(row-2,col-2);
	//初始化
	for(int i=0;i<A.row();++i){
		A[i][i] = 1;
	}
	A[0][1] = x[1]/(x[1]+x[2]);
	A[row-2-1][col-2-2] = x[row-1]/(x[row-2]+x[row-1]);
	Mat g(row-2,1);
	g[0][0] = 3*(x[2]/x[1]+x[2])*(y0[1]-y0[0])/(x[1]-x[0])+x[1]/(x[1]+x[2])*(y0[2]-y0[1])/(x[2]-x[1])-x[2]/(x[1]+x[2])*y1[1];
	g[row-2-1][0] = 3*(x[row-2+2-1]/(x[row-2+1-1]+x[row-2+2-1]))*(y0[row-2+1-1]-y0[row-2-1])/(x[row-2+1-1]-x[row-2-1])+x[row-2+1-1]/(x[row-2+1-1]+x[row-2+2-1])*(y0[row-2+2-1]-y0[row-2+1-1])/(x[row-2+2-1]-x[row-2+1-1])-x[row-2+1-1]/(x[row-2+1-1]+x[row-2+2-1])*y1[1];
	for(int i=1;i<row-2-1;++i){
		A[i][i-1] = x[i+2]/(x[i+1]+x[i+2]);
	    A[i][i+1] = x[i+1]/x[i+1]+x[i+2];
	   	g[i][0] = 3*(x[i+2]/(x[i+1]+x[i+2])*(y0[i+1]-y0[i])/(x0[i+1]-x0[i])+x[i+1]/(x[i+1]+x[i+2])*(y0[i+2]-y0[i+1])/(x[i+2]-x[i+1]));
	}
	// 计算给出m
	Mat tmp = A.inv()*g;
	std::vector<double> m;
	m.push_back(y1[0]);
	for(int i=0;i<g.size();++i){
		m.push_back(tmp[i][0]);
	}
	m.push_back(y1[1]);
	// 使用三次Hermite插值对每个小区间上的参数进行记录
	Mat f(row-1,4);
	for(int i=0;i<row-1;++i){
		//先将参数组织好
		std::vector<std::vector<double>> arg = {x[i],x[i+1]};
		Mat arg1(arg);
		arg = {y0[i],y0[i+1]};
		Mat arg2(arg);
		arg = {m[i],m[i+1]};
		Mat arg3(arg);
		f[i] = Hermite3(arg1,arg2,arg3);
	}
	return f;
}


int main(){
	return 0;
}
